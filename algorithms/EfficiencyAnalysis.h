#pragma once
#include <bits/stdc++.h>
using namespace std;

extern ofstream timeFile;
class EfficiencyAnalysis
{
private:
    chrono::time_point<chrono::steady_clock> startTime, endTime;
    long double elapsedSeconds = 0;

public:
    EfficiencyAnalysis()
    {
        startTime = chrono::steady_clock::now();
    }
    ~EfficiencyAnalysis()
    {
        endTime = chrono::steady_clock::now();
        elapsedSeconds = chrono::duration<long double>(endTime - startTime).count();
        timeFile << "Time: " << fixed << elapsedSeconds << " s\n";
    }
    long double elapsed() const { return elapsedSeconds; }
};