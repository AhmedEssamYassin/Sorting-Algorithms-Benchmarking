#pragma once
#include <chrono>
#include <fstream>
using namespace std;

extern ofstream timeFile;
class EfficiencyAnalysis
{
private:
    chrono::time_point<chrono::steady_clock> startTime, endTime;
    long double elapsedSeconds = 0;
    bool isStopped = false;

public:
    EfficiencyAnalysis()
    {
        startTime = chrono::steady_clock::now();
    }
    long double stop()
    {
        if (!isStopped)
        {
            endTime = chrono::steady_clock::now();
            elapsedSeconds = chrono::duration<long double>(endTime - startTime).count();
            isStopped = true;
        }
        return elapsedSeconds;
    }
    ~EfficiencyAnalysis()
    {
        if (!isStopped)
        {
            stop();
            timeFile << "Time: " << fixed << elapsedSeconds << " s\n";
        }
    }
    long double elapsed() const { return elapsedSeconds; }
};