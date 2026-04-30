#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
using namespace std;

class InsertionSort : public Sort
{
public:
    string getName() const override { return "InsertionSort"; }

    void insertionSort(vector<ll> &arr, int left, int right)
    {
        for (int i = left + 1; i <= right; i++)
        {
            ll key = arr[i];
            int j = i - 1;
            while (j >= left && arr[j] > key)
            {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;
        insertionSort(arr, 0, arr.size() - 1);
    }
};