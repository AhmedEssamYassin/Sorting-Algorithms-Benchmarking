#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
using namespace std;
#define ll long long
#define endl "\n"

class HeapSort : public Sort
{
private:
    void heapify(vector<ll> &arr, int n, int i)
    {
        int largest = i;       // Initialize largest as root
        int left = 2 * i + 1;  // left = 2*i + 1
        int right = 2 * i + 2; // right = 2*i + 2

        // If left child is larger than root
        if (left < n && arr[left] > arr[largest])
            largest = left;

        // If right child is larger than largest so far
        if (right < n && arr[right] > arr[largest])
            largest = right;

        // If largest is not root
        if (largest != i)
        {
            swap(arr[i], arr[largest]);

            // Recursively heapify the affected sub-tree
            heapify(arr, n, largest);
        }
    }

public:
    void sort(vector<ll> &arr) override
    {
        int n = arr.size();

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; i--)
        {
            // Move current root to end
            std::swap(arr[0], arr[i]);

            // Call max heapify on the reduced heap
            heapify(arr, i, 0);
        }
    }
};