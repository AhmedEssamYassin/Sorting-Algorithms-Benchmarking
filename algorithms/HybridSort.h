#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
#include "InsertionSort.h"
#include "HeapSort.h"
using namespace std;

#define HYBRID_INSERTION_THRESHOLD 64
#define rng(l, r) uniform_int_distribution<int64_t>(l, r)(Sort::rnd)

class HybridSort : public Sort
{
private:
    InsertionSort insertionSortHelper;
    HeapSort heapSortHelper;

    int hoarePartition(vector<ll> &arr, int low, int high)
    {
        int randomPivotIndex = rng(low, high);
        ll pivot = arr[randomPivotIndex];
        
        int i = low - 1;
        int j = high + 1;

        while (true)
        {
            do { i++; } while (arr[i] < pivot);
            do { j--; } while (arr[j] > pivot);
            if (i >= j) return j;
            swap(arr[i], arr[j]);
        }
    }

    void hybridSort(vector<ll> &arr, int left, int right, int depthLimit)
    {
        int size = right - left + 1;

        // Choose the sorting algorithm based on the sub_array size
        if (size < HYBRID_INSERTION_THRESHOLD)
        {
            insertionSortHelper.insertionSort(arr, left, right);
        }
        else if (depthLimit <= 0)
        {
            heapSortHelper.heapSort(arr, left, right);
        }
        else
        {
            int p = hoarePartition(arr, left, right);
            
            hybridSort(arr, left, p, depthLimit - 1);
            hybridSort(arr, p + 1, right, depthLimit - 1);
        }
    }

public:
    string getName() const override { return "HybridSort"; }

    // Wrapper function to call hybridSort with threshold values
    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;
        int maxDepth = 2 * __bit_width(arr.size()); // Use Merge Sort if depth exceeds this
        hybridSort(arr, 0, arr.size() - 1, maxDepth);
    }
};