#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
#include "InsertionSort.h"
#include "HeapSort.h"
using namespace std;

#define INSERTION_THRESHOLD 32

class QuickSort : public Sort
{
private:
    InsertionSort insertionSortHelper;
    HeapSort heapSortHelper;

    int partition(vector<ll> &arr, int low, int high)
    {
        ll pivot = arr[high]; // Select the last element as the pivot
        int i = low - 1;      // Index of the smaller element

        for (int j = low; j < high; j++)
        {
            // If the current element is smaller than or equal to the pivot
            if (arr[j] <= pivot)
            {
                i++; // Increment the index of the smaller element
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]); // Place pivot in its correct position
        return (i + 1);
    }

    void quickSort(vector<ll> &arr, int low, int high, int depthLimit)
    {
        if (low < high)
        {
            // Use Insertion Sort if the partition size is below the threshold
            if (high - low + 1 < INSERTION_THRESHOLD)
            {
                insertionSortHelper.insertionSort(arr, low, high);
            }
            else if (depthLimit <= 0)
            {
                heapSortHelper.heapSort(arr, low, high);
            }
            else
            {
                int pivotIndex = partition(arr, low, high);
                quickSort(arr, low, pivotIndex - 1, depthLimit - 1);
                quickSort(arr, pivotIndex + 1, high, depthLimit - 1);
            }
        }
    }

public:
    string getName() const override { return "QuickSort"; }

    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;
        int maxDepth = 2 * __bit_width(arr.size());
        quickSort(arr, 0, arr.size() - 1, maxDepth);
    }
};