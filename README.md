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
| File             | Description |
|-----------------|-------------|
| `sorting.cpp`   | Implementation of multiple sorting algorithms and efficiency analysis |
| `Efficiency_Analysis.h` | Header file for performance evaluation functions |
| `input.txt`     | Sample input file containing numbers to be sorted |
| `output.txt`    | Output file with sorted numbers |
| `time.txt`      | File storing execution time of sorting algorithms |
| `test.txt`      | File storing the verification of sorting algorithms |

## Performance Comparison
The performance of each sorting algorithm is measured based on execution time, and results are written to `time.txt`. The choice of sorting algorithm can be optimized based on the input size and data distribution.

### Expected Time and Space Complexities:

| Algorithm      | Best Case   | Average Case | Worst Case  | Space Complexity |
|--------------|------------|---------------|-------------|-----------------|
| Selection Sort | O(n²)      | O(n²)       | O(n²)       | O(1)            |
| Insertion Sort | O(n)       | O(n²)       | O(n²)       | O(1)            |
| Merge Sort    | O(n log n) | O(n log n)   | O(n log n)  | O(n)            |
| Quick Sort    | O(n log n) | O(n log n)   | O(n²)       | O(log n)        |
| Heap Sort     | O(n log n) | O(n log n)   | O(n log n)  | O(1)            |
| Count Sort    | O(n + k)   | O(n + k)     | O(n + k)    | O(n + k)        |
| Hybrid Sort   | O(n log n) | O(n log n)   | O(n log n)  | O(n)            |

> [!NOTE]
> the `k` in `Count Sort` is the size of possible numbers in the data set
 

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
| Number | Algorithm |
|--------|-----------|
| 0 | Selection Sort |
| 1 | Insertion Sort |
| 2 | Merge Sort |
| 3 | Quick Sort |
| 4 | Randomized Quick Sort|
| 5 | Heap Sort|
| 6 | Count Sort|
| 7 | Hybrid Sort |

Example usage:
```
./sorting 3 tests/input1000000.txt output.txt time.txt test.txt
```
(This runs Quick Sort on `input1000000.txt` and writes the results to `output.txt` while logging the execution time in `time.txt` and verification of the `Quick Sort` in `test.txt`.)

## Test Case Generation
Random test cases are generated using the following method:

```
function<uint64_t()> random_address = []() -> uint64_t
{
	char *p = new char;
	delete p;
	return uint64_t(p);
};
const uint64_t SEED = chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1);
std::mt19937 rnd(SEED);
#define rng(l, r) uniform_int_distribution<int64_t>(l, r)(rnd)
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
### Compilation:
Use the following command to compile the program:
```
g++ -O3 -o sorting sorting.cpp
```
### Running:
```
./sorting 2 tests/input1000.txt output.txt time.txt test.txt
```
This runs `Merge Sort` on `input1000.txt` and outputs the sorted numbers to `output.txt` while logging the execution time in `time.txt` and verify that the `Merge Sort` algorithm sorts data correctly without modifying it in `test.txt`.

> [!NOTE]
> If you want to test all algorithms simultaneously:
> - Pass the `dataSet` by value instead of by reference 
> - Comment all `break` statements except the one before the `default` statement in the switch-case.
