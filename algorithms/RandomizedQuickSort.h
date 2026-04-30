#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
#include "InsertionSort.h"
#include "HeapSort.h"
using namespace std;

#define INSERTION_THRESHOLD 32
#define rng(l, r) uniform_int_distribution<int64_t>(l, r)(Sort::rnd)

class RandomizedQuickSort : public Sort
{
private:
    InsertionSort insertionSortHelper;
    HeapSort heapSortHelper;

    int randomizedPartition(vector<ll> &arr, int low, int high)
    {
        // Pick a random pivot index between low and high
        int randomPivotIndex = rng(low, high);

        // Swap the randomly chosen pivot with the last element
        swap(arr[randomPivotIndex], arr[high]);

        ll pivot = arr[high];
        int i = low - 1;

        // Standard partition process
        for (int j = low; j < high; j++)
        {
            if (arr[j] <= pivot)
            {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    // Randomized quicksort function
    void randomizedQuickSort(vector<ll> &arr, int low, int high, int depthLimit)
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
                int pivotIndex = randomizedPartition(arr, low, high);
                randomizedQuickSort(arr, low, pivotIndex - 1, depthLimit - 1);
                randomizedQuickSort(arr, pivotIndex + 1, high, depthLimit - 1);
            }
        }
    }

public:
    string getName() const override { return "RandomizedQuickSort"; }

    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;
        int maxDepth = 2 * __bit_width(arr.size());
        randomizedQuickSort(arr, 0, arr.size() - 1, maxDepth);
    }
};