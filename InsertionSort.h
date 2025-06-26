#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
using namespace std;
#define ll long long
#define endl "\n"

class InsertionSort : public Sort
{
private:
    int left, right;

public:
    InsertionSort() : left(-1), right(-1) {}
    void setInterval(int l, int r)
    {
        left = l;
        right = r;
    }
    virtual void sort(vector<ll> &arr) override
    {
        if (left == -1 && right == -1)
            left = 0, right = arr.size() - 1;
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
};