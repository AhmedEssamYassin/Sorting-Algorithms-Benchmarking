#include <bits/stdc++.h>
#include "Efficiency_Analysis.h"
#include "Sort.h"
#include "InsertionSort.h"
#include "SelectionSort.h"
#include "MergeSort.h"
#include "QuickSort.h"
#include "RandomizedQuickSort.h"
#include "HeapSort.h"
#include "CountSort.h"
#include "HybridSort.h"
using namespace std;
#define ll long long
#define endl "\n"

Efficiency_Analysis *E;
ofstream timeFile;
ofstream testFile;

function<uint64_t()> random_address = []() -> uint64_t
{
    char *p = new char;
    delete p;
    return uint64_t(p);
};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
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
        outFile << num << endl;
}

bool haveSameElements(const vector<ll> &a, const vector<ll> &b)
{
    if (a.size() != b.size())
        return false;

    map<ll, int> freq;
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
void verify(const vector<ll> &data, Sort *sorter)
{
    string sorterType = "Unknown Sorter";
    int sorterID = -1;

    if (dynamic_cast<SelectionSort *>(sorter))
    {
        sorterType = "SelectionSort";
        sorterID = 0;
    }
    else if (dynamic_cast<InsertionSort *>(sorter))
    {
        sorterType = "InsertionSort";
        sorterID = 1;
    }
    else if (dynamic_cast<MergeSort *>(sorter))
    {
        sorterType = "MergeSort";
        sorterID = 2;
    }
    else if (dynamic_cast<QuickSort *>(sorter))
    {
        sorterType = "QuickSort";
        sorterID = 3;
    }
    else if (dynamic_cast<RandomizedQuickSort *>(sorter))
    {
        sorterType = "RandomizedQuickSort";
        sorterID = 4;
    }
    else if (dynamic_cast<HeapSort *>(sorter))
    {
        sorterType = "HeapSort";
        sorterID = 5;
    }
    else if (dynamic_cast<CountSort *>(sorter))
    {
        sorterType = "CountSort";
        sorterID = 6;
    }
    else if (dynamic_cast<HybridSort *>(sorter))
    {
        sorterType = "HybridSort";
        sorterID = 7;
    }

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

void SortInterface(vector<ll> &data, Sort *sorter)
{
    E = new Efficiency_Analysis();
    sorter->sort(data);
    delete E; // Do not include time of verification
    verify(data, sorter);
}

int main(int argc, char *argv[])
{
    // g++ -O3 -o sorting sorting.cpp
    //./sorting 4 input.txt output.txt time.txt
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    if (argc != 6)
    {
        std::cerr << "Usage: " << argv[0] << " <algorithm_number> <input_file> <output_file> <time_file> <test_file>" << endl;
        return 1;
    }

    int algorithmNumber = stoi(argv[1]);
    string inputFilePath = argv[2];
    string outputFilePath = argv[3];
    string timeFilePath = argv[4];
    string testFilePath = argv[5];
    // Read data from input file
    vector<ll> dataSet = readData(inputFilePath);
    vector<ll> dataSetCopy = dataSet; // To try std::sort() on
    originalData = dataSet;           // To verify that algorithms doesn't modify the data
    // Instantiate the selected sorting algorithm
    timeFile.open(timeFilePath);
    testFile.open(testFilePath);
    timeFile << "Testing on data size = " << dataSet.size() << endl;
    Sort *sorter;
    switch (algorithmNumber)
    {
    case SELECTION_SORT:
        timeFile << "Using Selection Sort\n";
        sorter = new SelectionSort();
        SortInterface(dataSet, sorter);
        break;
    case INSERTION_SORT:
        timeFile << "Using Insertion Sort\n";
        sorter = new InsertionSort();
        SortInterface(dataSet, sorter);
        break;
    case MERGE_SORT:
        timeFile << "Using Merge Sort\n";
        sorter = new MergeSort();
        SortInterface(dataSet, sorter);
        break;
    case QUICK_SORT:
        timeFile << "Using Quick Sort\n";
        sorter = new QuickSort();
        SortInterface(dataSet, sorter);
        break;
    case RANDOMIZED_QUICK_SORT:
        timeFile << "Using Randomized Quick Sort\n";
        sorter = new RandomizedQuickSort();
        SortInterface(dataSet, sorter);
        break;
    case HEAP_SORT:
        timeFile << "Using Heap Sort\n";
        sorter = new HeapSort();
        SortInterface(dataSet, sorter);
        break;
    case COUNT_SORT:
        timeFile << "Using Count Sort\n";
        sorter = new CountSort();
        SortInterface(dataSet, sorter);
        break;
    case HYBRID_SORT:
        timeFile << "Using Hybrid Sort\n";
        sorter = new HybridSort();
        SortInterface(dataSet, sorter);
        break;
    default:
        std::cerr << "Invalid algorithm number.\nUse:\n0 for Selection Sort\n1 for Insertion Sort\n"
                  << "2 for Merge Sort\n3 for Quick Sort\n4 for Randomized Quick Sort\n5 for Heap Sort\n6 for Count Sort\n"
                  << "7 for Hybrid Sort." << endl;
        return 1;
    }

    E = new Efficiency_Analysis();
    sort(dataSetCopy.begin(), dataSetCopy.end());
    timeFile << "Using std Sort\n";
    delete E;
    // Write sorted data to output file
    writeData(dataSet, outputFilePath);

    return 0;
}