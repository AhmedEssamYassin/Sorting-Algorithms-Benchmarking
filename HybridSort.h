#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
using namespace std;
#define ll long long
#define endl "\n"

#define rng(l, r) uniform_int_distribution<int64_t>(l, r)(Sort::rnd)

class HybridSort : public Sort
{
private:
    int left, right, insertionThreshold, mergeThreshold;
    InsertionSort insertionSortHelper;
    MergeSort mergeSortHelper;

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

    void hybridSort(vector<ll> &arr, int left, int right, int insertionThreshold, int mergeThreshold)
    {
        int size = right - left + 1;

        // Choose the sorting algorithm based on the sub_array size
        if (size < insertionThreshold)
        {
            insertionSortHelper.setInterval(left, right);
            insertionSortHelper.sort(arr);
        }

        else if (mergeThreshold == 0)
        {
            mergeSortHelper.setInterval(left, right);
            mergeSortHelper.sort(arr);
        }
        else
        {
            int pivotIndex = randomizedPartition(arr, left, right);
            hybridSort(arr, left, pivotIndex - 1, insertionThreshold, mergeThreshold - 1);
            hybridSort(arr, pivotIndex + 1, right, insertionThreshold, mergeThreshold - 1);
        }
    }

public:
    // Wrapper function to call hybridSort with threshold values
    void sort(vector<ll> &arr) override
    {
        int insertionThreshold = 64;                      // Use Insertion Sort for arrays smaller than this
        int mergeThreshold = 2 * __bit_width(arr.size()); // Use Merge Sort for arrays larger than this
        hybridSort(arr, 0, arr.size() - 1, insertionThreshold, mergeThreshold);
    }
};