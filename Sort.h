#pragma once
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define endl "\n"

class Sort
{

public:
    static std::mt19937 rnd;
    // Pure virtual function
    virtual void sort(vector<ll> &arr) = 0;
    virtual ~Sort() {}
};