#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
using namespace std;

class HeapSort : public Sort
{
private:
    void heapifyRange(vector<ll> &arr, int n, int i, int offset)
    {
        int largest = i;
        int leftChild = 2 * i + 1;
        int rightChild = 2 * i + 2;

        if (leftChild < n && arr[offset + leftChild] > arr[offset + largest])
            largest = leftChild;

        if (rightChild < n && arr[offset + rightChild] > arr[offset + largest])
            largest = rightChild;

        if (largest != i)
        {
            swap(arr[offset + i], arr[offset + largest]);
            heapifyRange(arr, n, largest, offset);
        }
    }

public:
    string getName() const override { return "HeapSort"; }

    void heapSort(vector<ll> &arr, int left, int right)
    {
        int n = right - left + 1;
        if (n <= 1) return;

        // Build heap (rearrange array)
        for (int i = n / 2 - 1; i >= 0; i--)
            heapifyRange(arr, n, i, left);

        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; i--)
        {
            // Move current root to end
            std::swap(arr[left], arr[left + i]);

            // Call max heapify on the reduced heap
            heapifyRange(arr, i, 0, left);
        }
    }

    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;
        heapSort(arr, 0, arr.size() - 1);
    }
};