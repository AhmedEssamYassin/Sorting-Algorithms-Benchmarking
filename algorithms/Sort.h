#pragma once
#include <bits/stdc++.h>
using namespace std;
#define ll long long

class Sort
{

public:
    static std::mt19937 rnd;
    // Pure virtual functions
    virtual void sort(vector<ll> &arr) = 0;
    virtual string getName() const = 0;
    virtual ~Sort() {}
};