#pragma once
#include <utility>
#include <bit>
#include "Sort.h"
#include "InsertionSort.h"
#include "HeapSort.h"
using namespace std;

class QuickSort : public Sort
{
private:
    InsertionSort insertionSortHelper;
    HeapSort heapSortHelper;

    int hoarePartition(vector<ll> &arr, int low, int high)
    {
        ll pivot = arr[low + (high - low) / 2];
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
                int p = hoarePartition(arr, low, high);
                quickSort(arr, low, p, depthLimit - 1);
                quickSort(arr, p + 1, high, depthLimit - 1);
            }
        }
    }

public:
    string getName() const override { return "QuickSort"; }

    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;
        int maxDepth = 2 * std::bit_width(arr.size());
        quickSort(arr, 0, arr.size() - 1, maxDepth);
    }
};