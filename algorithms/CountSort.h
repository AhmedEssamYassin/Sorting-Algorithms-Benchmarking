#pragma once
#include <bits/stdc++.h>
#include "Sort.h"
using namespace std;

#define COUNT_MAX_VALUE 10000000

class CountSort : public Sort
{
public:
    string getName() const override { return "CountSort"; }

    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;

        ll minValue = *min_element(arr.begin(), arr.end());
        ll maxValue = *max_element(arr.begin(), arr.end());
        
        if (maxValue - minValue > COUNT_MAX_VALUE)
            throw runtime_error("Max range cannot exceed COUNT_MAX_VALUE due to memory and time issues.");
            
        vector<int> freq(maxValue - minValue + 1, 0);
        for (const ll &x : arr)
            freq[x - minValue]++;
            
        for (ll i = minValue, j = 0; i <= maxValue; i++)
        {
            while (freq[i - minValue]-- > 0)
                arr[j++] = i;
        }
    }
};