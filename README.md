# Sorting Algorithms Comparison and Implementation

## Overview
This file implements and compares various sorting algorithms based on their efficiency, runtime, and suitability for different input sizes. The sorting algorithms included are:

- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort
- Randomized Quick Sort
- Heap Sort
- Count Sort
- Hybrid Sort (combining multiple strategies)

## File Structure
| File / Directory                   | Description                                                                         |
| ---------------------------------- | ----------------------------------------------------------------------------------- |
| `sorting.cpp`                      | Main entry point — reads data, dispatches to the selected algorithm, writes results |
| `algorithms/Sort.h`                | Abstract base class for all sorting algorithms                                      |
| `algorithms/EfficiencyAnalysis.h`  | RAII stopwatch timer used for benchmarking                                          |
| `algorithms/SelectionSort.h`       | Selection Sort implementation                                                       |
| `algorithms/InsertionSort.h`       | Insertion Sort implementation (also used as a sub-routine by other sorts)           |
| `algorithms/MergeSort.h`           | Merge Sort with Insertion Sort fallback for small partitions                        |
| `algorithms/QuickSort.h`           | Quick Sort with Hoare partition, Insertion Sort + Heap Sort fallbacks               |
| `algorithms/RandomizedQuickSort.h` | Randomized Quick Sort with Hoare partition and Introsort fallbacks                  |
| `algorithms/HeapSort.h`            | Heap Sort implementation (also used as a depth-limit fallback)                      |
| `algorithms/CountSort.h`           | Counting Sort for integer data with bounded range                                   |
| `algorithms/HybridSort.h`          | Hybrid Introsort combining Quick Sort, Heap Sort, and Insertion Sort                |
| `benchmark.py`                     | Runs all algorithms across all test inputs and records timing/verification          |
| `check_tests.py`                   | Scans result files for verification failures                                        |
| `compare_std.py`                   | Reports which algorithms beat `std::sort` at each dataset size                      |
| `Makefile`                         | Build and automation targets (`benchmark`, `check`, `compare`, `analyze`)           |
| `tests/`                           | Directory containing input datasets (`input10.txt` … `input1000000.txt`)            |
| `results/`                         | Directory where per-algorithm output, timing, and test files are written            |

## Performance Comparison
The performance of each sorting algorithm is measured based on execution time, and results are written to `time.txt`. The choice of sorting algorithm can be optimized based on the input size and data distribution.

### Expected Time and Space Complexities:

| Algorithm             | Best Case  | Average Case | Worst Case  | Space Complexity |
| --------------------- | ---------- | ------------ | ----------- | ---------------- |
| Selection Sort        | O(n²)      | O(n²)        | O(n²)       | O(1)             |
| Insertion Sort        | O(n)       | O(n²)        | O(n²)       | O(1)             |
| Merge Sort            | O(n log n) | O(n log n)   | O(n log n)  | O(n)             |
| Quick Sort            | O(n log n) | O(n log n)   | O(n log n)* | O(n)             |
| Randomized Quick Sort | O(n log n) | O(n log n)   | O(n log n)* | O(n)             |
| Heap Sort             | O(n log n) | O(n log n)   | O(n log n)  | O(1)             |
| Count Sort            | O(n + k)   | O(n + k)     | O(n + k)    | O(n + k)         |
| Hybrid Sort           | O(n log n) | O(n log n)   | O(n log n)  | O(n)             |

> [!NOTE]
> * Quick Sort and Randomized Quick Sort fallback to Heap Sort if recursion depth exceeds limits (Introsort pattern), guaranteeing O(n log n) worst-case time complexity, but taking O(n) space.
> 
> * The `k` in `Count Sort` is the range of possible numbers in the data set (`max - min + 1`).

## Command-Line Arguments
The program takes the following command-line arguments:
```
./sorting <algorithm_number> <input_file> <output_file> <time_file> <test_file>
```

Where:
- `<algorithm_number>`: Specifies which sorting algorithm to use (see below).
- `<input_file>`: Path to the file containing unsorted numbers.
- `<output_file>`: Path to save the sorted output.
- `<time_file>`: Path to store execution time.
- `<test_file>`: Path to store Verification of algorithms.

### Algorithm Selection:
| Number | Algorithm             |
| ------ | --------------------- |
| 0      | Selection Sort        |
| 1      | Insertion Sort        |
| 2      | Merge Sort            |
| 3      | Quick Sort            |
| 4      | Randomized Quick Sort |
| 5      | Heap Sort             |
| 6      | Count Sort            |
| 7      | Hybrid Sort           |

Example usage:
```
./sorting 3 tests/input1000000.txt output.txt time.txt test.txt
```
(This runs Quick Sort on `input1000000.txt` and writes the results to `output.txt` while logging the execution time in `time.txt` and verification of the `Quick Sort` in `test.txt`.)

## Test Case Generation
Random test cases are generated using the following method:

```cpp
function<uint64_t()> randomAddress = []() -> uint64_t
{
    char *p = new char;
    uint64_t addr = reinterpret_cast<uint64_t>(p);
    delete p;
    return addr;
};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (randomAddress() | 1);
std::mt19937 Sort::rnd(SEED);
```
Dataset Sizes:
Sorting algorithms are tested on different input sizes:

- 10
- 100
- 1,000
- 10,000
- 100,000
- 500,000
- 1,000,000

## How to Build and Run

### Using Makefile (Recommended)
The project includes a `Makefile` and Python scripts for automated benchmarking, verification, and performance comparison against `std::sort`.

- `make benchmark`: Compiles the code and runs all sorting algorithms across the available datasets in `tests/`.
- `make check`: Validates the output of the sorted arrays to ensure correctness without data corruption.
- `make compare`: Compares the execution times of the implemented algorithms against `std::sort`.
- `make analyze`: Runs `benchmark`, `check`, and `compare` sequentially.

Example:
```bash
make analyze
```

### Manual Compilation
Use the following command to compile the program (requires C++20 for `<bit>` operations):
```bash
g++ -O3 -std=c++20 -o sorting sorting.cpp
```

### Manual Running
```bash
./sorting 2 tests/input1000.txt output.txt time.txt test.txt
```
This runs `Merge Sort` on `input1000.txt` and outputs the sorted numbers to `output.txt` while logging the execution time in `time.txt` and verifying that the `Merge Sort` algorithm sorts data correctly without modifying it in `test.txt`.

> [!NOTE]
> If you want to test all algorithms simultaneously manually inside `sorting.cpp`:
> - Pass the `dataset` by value instead of by reference 
> - Comment all `break` statements except the one before the `default` statement in the switch-case.
