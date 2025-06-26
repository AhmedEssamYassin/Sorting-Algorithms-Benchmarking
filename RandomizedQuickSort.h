#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
using namespace std;
#define ll long long
#define endl "\n"

#define rng(l, r) uniform_int_distribution<int64_t>(l, r)(Sort::rnd)

class RandomizedQuickSort : public Sort
{
private:
    const int insertionThreshold;
    InsertionSort insertionSortHelper;

    bool isSorted(const vector<ll> &arr, int left, int right)
    {
        for (int i = left; i < right; i++)
        {
            if (arr[i] > arr[i + 1])
                return false;
        }
        return true;
    }
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
    void randomizedQuickSort(vector<ll> &arr, int low, int high, int insertionThreshold)
    {
        if (low < high)
        {
            if (isSorted(arr, low, high))
                return;
            // Use Insertion Sort if the partition size is below the threshold
            if (high - low + 1 < insertionThreshold)
            {
                insertionSortHelper.setInterval(low, high);
                insertionSortHelper.sort(arr);
            }
            else
            {
                int pivotIndex = randomizedPartition(arr, low, high);
                randomizedQuickSort(arr, low, pivotIndex - 1, insertionThreshold);
                randomizedQuickSort(arr, pivotIndex + 1, high, insertionThreshold);
            }
        }
    }

public:
    RandomizedQuickSort() : insertionThreshold(32) {}
    virtual void sort(vector<ll> &arr) override
    {
        randomizedQuickSort(arr, 0, arr.size() - 1, insertionThreshold);
    }
};