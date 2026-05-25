#pragma once
#include <utility>
#include "Sort.h"
using namespace std;

class SelectionSort : public Sort
{
public:
    string getName() const override { return "SelectionSort"; }
    
    void sort(vector<ll> &arr) override
    {
        if (arr.empty()) return;
        
        int n = arr.size();
        for (int i = 0; i < n - 1; i++)
        {
            // Find the minimum element in the unsorted portion of the array
            int minIndex = i;
            for (int j = i + 1; j < n; j++)
            {
                if (arr[j] < arr[minIndex])
                    minIndex = j;
            }
            // Swap the found minimum element with the first element of the unsorted portion
            if (minIndex != i)
                swap(arr[i], arr[minIndex]);
        }
    }
};