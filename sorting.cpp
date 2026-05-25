#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <unordered_map>
#include <functional>
#include <memory>
#include <iomanip>
#include "algorithms/EfficiencyAnalysis.h"
#include "algorithms/Sort.h"
#include "algorithms/InsertionSort.h"
#include "algorithms/SelectionSort.h"
#include "algorithms/MergeSort.h"
#include "algorithms/QuickSort.h"
#include "algorithms/RandomizedQuickSort.h"
#include "algorithms/HeapSort.h"
#include "algorithms/CountSort.h"
#include "algorithms/HybridSort.h"
using namespace std;
#define ll long long

ofstream timeFile;
ofstream testFile;

function<uint64_t()> randomAddress = []() -> uint64_t
{
    char *p = new char;
    uint64_t addr = reinterpret_cast<uint64_t>(p);
    delete p;
    return addr;
};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (randomAddress() | 1);
std::mt19937 Sort::rnd(SEED);

enum
{
    SELECTION_SORT = 0,
    INSERTION_SORT,
    MERGE_SORT,
    QUICK_SORT,
    RANDOMIZED_QUICK_SORT,
    HEAP_SORT,
    COUNT_SORT,
    HYBRID_SORT
};

vector<ll> readData(const string &filePath)
{
    ifstream inFile(filePath);
    if (!inFile)
    {
        cerr << "Error: Could not open input file " << filePath << "\n";
        exit(1);
    }
    vector<ll> data;
    ll number;
    while (inFile >> number)
        data.push_back(number);
    return data;
}

// Function to write sorted data to a file
void writeData(const vector<ll> &data, const string &filePath)
{
    ofstream outFile(filePath);
    for (const ll &num : data)
        outFile << num << "\n";
}

bool haveSameElements(const vector<ll> &a, const vector<ll> &b)
{
    if (a.size() != b.size())
        return false;

    unordered_map<ll, int> freq;
    for (ll x : a)
        ++freq[x];
    for (const ll &x : b)
    {
        if (freq.find(x) == freq.end() || freq[x] == 0)
            return false;
        --freq[x];
    }
    return true;
}

vector<ll> originalData;
void verify(const vector<ll> &data, Sort *sorter, int sorterID)
{
    string sorterType = sorter->getName();
    bool sorted = is_sorted(data.begin(), data.end());
    bool sameElements = haveSameElements(originalData, data);

    if (sorted && sameElements)
    {
        testFile << "[" << sorterID << "] " << sorterType << " ✅ Sort verified: correct order and elements preserved.\n";
    }
    else
    {
        testFile << "[" << sorterID << "] " << sorterType << " ❌ Verification failed: ";
        if (!sorted)
            testFile << "data not sorted. ";
        if (!sameElements)
            testFile << "elements mismatch with original.\n";
    }
}

// Times the given sorter and std::sort on the same data, then writes a comparison to timeFile.
void sortInterface(vector<ll> &data, unique_ptr<Sort> sorter, int sorterID, vector<ll> &datasetCopy)
{
    string algoName = sorter->getName();

    // --- Time the custom algorithm ---
    timeFile << algoName << "\n";
    EfficiencyAnalysis algoTimer;
    sorter->sort(data);
    long double algoTime = algoTimer.stop();
    timeFile << "Time: " << fixed << setprecision(6) << algoTime << " s\n";

    verify(data, sorter.get(), sorterID);

    // --- Time std::sort on the same original data ---
    timeFile << "std::sort\n";
    EfficiencyAnalysis stdTimer;
    sort(datasetCopy.begin(), datasetCopy.end());
    long double stdTime = stdTimer.stop();
    timeFile << "Time: " << fixed << setprecision(6) << stdTime << " s\n";

    // --- Comparison summary ---
    timeFile << "\nComparison: " << algoName << " is ";
    if (stdTime > 0)
    {
        long double ratio = algoTime / stdTime;
        if (ratio <= 1.05L)
            timeFile << "on par with std::sort";
        else
            timeFile << fixed << setprecision(2) << ratio << "x slower than std::sort";
    }
    else
    {
        timeFile << "comparable to std::sort (both too fast to measure)";
    }
    timeFile << "\n\n";
}

int main(int argc, char *argv[])
{
    // g++ -O3 -o sorting sorting.cpp
    //./sorting 4 input.txt output.txt time.txt test.txt
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (argc != 6)
    {
        cerr << "Usage: " << argv[0] << " <algorithm_number> <input_file> <output_file> <time_file> <test_file>\n";
        return 1;
    }

    int algorithmNumber = stoi(argv[1]);
    string inputFilePath = argv[2];
    string outputFilePath = argv[3];
    string timeFilePath = argv[4];
    string testFilePath = argv[5];

    // Read data from input file
    vector<ll> dataset = readData(inputFilePath);
    vector<ll> datasetCopy = dataset; // For std::sort comparison
    originalData = dataset;           // For verification

    timeFile.open(timeFilePath);
    testFile.open(testFilePath);
    timeFile << "Dataset size = " << dataset.size() << "\n\n";

    switch (algorithmNumber)
    {
    case SELECTION_SORT:
        sortInterface(dataset, make_unique<SelectionSort>(), algorithmNumber, datasetCopy);
        break;
    case INSERTION_SORT:
        sortInterface(dataset, make_unique<InsertionSort>(), algorithmNumber, datasetCopy);
        break;
    case MERGE_SORT:
        sortInterface(dataset, make_unique<MergeSort>(), algorithmNumber, datasetCopy);
        break;
    case QUICK_SORT:
        sortInterface(dataset, make_unique<QuickSort>(), algorithmNumber, datasetCopy);
        break;
    case RANDOMIZED_QUICK_SORT:
        sortInterface(dataset, make_unique<RandomizedQuickSort>(), algorithmNumber, datasetCopy);
        break;
    case HEAP_SORT:
        sortInterface(dataset, make_unique<HeapSort>(), algorithmNumber, datasetCopy);
        break;
    case COUNT_SORT:
        sortInterface(dataset, make_unique<CountSort>(), algorithmNumber, datasetCopy);
        break;
    case HYBRID_SORT:
        sortInterface(dataset, make_unique<HybridSort>(), algorithmNumber, datasetCopy);
        break;
    default:
        cerr << "Invalid algorithm number.\nUse:\n0 for Selection Sort\n1 for Insertion Sort\n"
             << "2 for Merge Sort\n3 for Quick Sort\n4 for Randomized Quick Sort\n5 for Heap Sort\n6 for Count Sort\n"
             << "7 for Hybrid Sort.\n";
        return 1;
    }

    // Write sorted data to output file
    writeData(dataset, outputFilePath);

    return 0;
}