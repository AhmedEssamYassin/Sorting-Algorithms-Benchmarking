#pragma once
#include <bits/stdc++.h>
using namespace std;

extern ofstream timeFile;
class Efficiency_Analysis
{
private:
    chrono::time_point<chrono::high_resolution_clock> Start_Time, End_Time;
    chrono::duration<long double> elapsed_time;

public:
    Efficiency_Analysis()
    {
        Start_Time = chrono::high_resolution_clock::now();
    }
    ~Efficiency_Analysis()
    {
        End_Time = chrono::high_resolution_clock::now();
        elapsed_time = (End_Time - Start_Time);
        timeFile << "Time consumed to execute this block of code is: " << fixed << elapsed_time.count() << " s" << "\n\n";
    }
};