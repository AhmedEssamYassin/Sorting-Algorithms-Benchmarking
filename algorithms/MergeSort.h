#pragma once
#include "Sort.h"
#include "InsertionSort.h"
using namespace std;

class MergeSort : public Sort
{
private:
    InsertionSort insertionSortHelper;

    void merge(vector<ll> &vc, vector<ll> &temp, int left, int mid, int right)
    {
        int p = left, q = mid + 1; // To traverse the left and the right segment respectively
        int k = left;
        for (int i{left}; i <= right; i++)
        {
            if (p > mid) // First segment comes to an end
                temp[k++] = vc[q++];
            else if (q > right) // Second segment comes to an end
                temp[k++] = vc[p++];
            else if (vc[p] <= vc[q]) // The first segment has the smaller element
                temp[k++] = vc[p++];
            else // The second segment has the smaller element
                temp[k++] = vc[q++];
        }

        // Overwriting the original elements in a sorted manner
        for (int i = left; i <= right; i++)
            vc[i] = temp[i];
    }

    void mergeSort(vector<ll> &arr, vector<ll> &temp, int left, int right)
    {
        if (left < right)
        {
            // Use Insertion Sort if the partition size is below the insertionThreshold
            if (right - left + 1 < INSERTION_THRESHOLD)
            {
                insertionSortHelper.insertionSort(arr, left, right);
            }
            else
            {
                int mid = left + (right - left) / 2;
                mergeSort(arr, temp, left, mid);
                mergeSort(arr, temp, mid + 1, right);
                merge(arr, temp, left, mid, right);
            }
        }
    }

public:
    string getName() const override { return "MergeSort"; }

    void mergeSort(vector<ll> &arr, int left, int right)
    {
        vector<ll> temp(arr.size());
        mergeSort(arr, temp, left, right);
    }

    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;
        vector<ll> temp(arr.size());
        mergeSort(arr, temp, 0, arr.size() - 1);
    }
};
