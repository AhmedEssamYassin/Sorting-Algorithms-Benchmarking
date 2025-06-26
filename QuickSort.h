#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
#include "InsertionSort.h"
#include "MergeSort.h"
using namespace std;
#define ll long long
#define endl "\n"

class QuickSort : public Sort
{
private:
    int left, right, insertionThreshold, mergeThreshold;
    InsertionSort insertionSortHelper;
    MergeSort mergeSortHelper;

    bool isSorted(const vector<ll> &arr, int left, int right)
    {
        for (int i = left; i < right; i++)
        {
            if (arr[i] > arr[i + 1])
                return false;
        }
        return true;
    }
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

    void quickSort(vector<ll> &arr, int low, int high, int insertionThreshold, int mergeThreshold)
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

            else if (high - low + 1 > mergeThreshold)
            {
                mergeSortHelper.setInterval(low, high);
                mergeSortHelper.sort(arr);
            }

            else
            {
                int pivotIndex = partition(arr, low, high);
                quickSort(arr, low, pivotIndex - 1, insertionThreshold, 2 * __bit_width(high - low + 1));
                quickSort(arr, pivotIndex + 1, high, insertionThreshold, 2 * __bit_width(high - low + 1));
            }
        }
    }

public:
    QuickSort() : left(-1), right(-1) {}
    void setData(int l, int r)
    {
        left = l;
        right = r;
    }
    virtual void sort(vector<ll> &arr) override
    {
        if (left == -1 && right == -1)
            left = 0, right = arr.size() - 1;
        insertionThreshold = 32;
        mergeThreshold = 2 * __bit_width(arr.size());
        quickSort(arr, left, right, insertionThreshold, mergeThreshold);
    }
};