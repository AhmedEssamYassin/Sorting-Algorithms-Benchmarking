#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
using namespace std;
#define ll long long
#define endl "\n"

class CountSort : public Sort
{
private:
    ll minValue, maxValue;
    int freq[10000001];

public:
    CountSort() {}
    virtual void sort(vector<ll> &arr) override
    {
        minValue = *min_element(arr.begin(), arr.end());
        maxValue = *max_element(arr.begin(), arr.end());
        if (maxValue > 1e7)
            throw "Max value cannot exceed 1e7 due to memory and time issues.";
        for (const ll &x : arr)
            freq[x]++;
        for (int i = minValue, j = 0; i <= maxValue; i++)
        {
            while (freq[i]-- > 0)
                arr[j++] = i;
        }
    }
};