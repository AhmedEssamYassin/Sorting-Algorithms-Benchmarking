#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
#include "InsertionSort.h"
using namespace std;
#define ll long long
#define endl "\n"

class MergeSort : public Sort
{
private:
    int left, right, insertionThreshold;
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
    void merge(vector<ll> &vc, int left, int mid, int right)
    {
        int p = left, q = mid + 1; // To traverse the left and the right segment respectively
        vector<ll> temp;
        for (int i{left}; i <= right; i++)
        {
            if (p > mid) // First segment comes to an end
                temp.push_back(vc[q++]);
            else if (q > right) // Second segment comes to an end
                temp.push_back(vc[p++]);
            else if (vc[p] <= vc[q]) // The first segment has the smaller element
                temp.push_back(vc[p++]);
            else // The second segment has the smaller element
                temp.push_back(vc[q++]);
        }

        // Overwriting the original elements in a sorted manner
        for (int i = 0; i < temp.size(); i++)
            vc[left++] = temp[i];
    }

    void mergeSort(vector<ll> &arr, int left, int right, int insertionThreshold)
    {
        if (left < right)
        {
            if (isSorted(arr, left, right))
                return;
            // Use Insertion Sort if the partition size is below the insertionThreshold
            if (right - left + 1 < insertionThreshold)
            {
                insertionSortHelper.setInterval(left, right);
                insertionSortHelper.sort(arr);
            }
            else
            {
                int mid = left + (right - left) / 2;
                mergeSort(arr, left, mid, insertionThreshold);
                mergeSort(arr, mid + 1, right, insertionThreshold);
                merge(arr, left, mid, right);
            }
        }
    }

public:
    MergeSort() : left(-1), right(-1) {}
    void setInterval(int l, int r)
    {
        left = l;
        right = r;
    }
    void sort(vector<ll> &arr) override
    {
        if (left == -1 && right == -1)
            left = 0, right = arr.size() - 1;
        insertionThreshold = 32;
        mergeSort(arr, left, right, insertionThreshold);
    }
};
