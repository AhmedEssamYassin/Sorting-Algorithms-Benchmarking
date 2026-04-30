import os
import subprocess
import glob
import time

algorithms = {
    0: "SelectionSort",
    1: "InsertionSort",
    2: "MergeSort",
    3: "QuickSort",
    4: "RandomizedQuickSort",
    5: "HeapSort",
    6: "CountSort",
    7: "HybridSort"
}

# Find all input files and sort them by numerical value in their names (e.g., input10.txt -> 10)
inputs = glob.glob("tests/input*.txt")
inputs.sort(key=lambda f: int(''.join(filter(str.isdigit, f)) or 0))

executable = "sorting.exe" if os.name == "nt" else "./sorting"

for algoId, algoName in algorithms.items():
    # Each algorithm writes into its own subfolder
    algoDir = os.path.join("results", algoName)
    os.makedirs(algoDir, exist_ok=True)

    print(f"\n{'='*50}\nStarting Benchmark: {algoName}\n{'='*50}")
    for inputFile in inputs:
        baseName = os.path.splitext(os.path.basename(inputFile))[0]

        # O(N^2) algorithms will take too long on sizes >= 100000
        size = int(''.join(filter(str.isdigit, baseName)) or 0)
        if (algoId == 0 or algoId == 1) and size > 100000:
            print(f"Skipping {algoName} on {baseName} (O(N^2) too slow for N > 100000)")
            continue

        outputFile = os.path.join(algoDir, f"{baseName}_output.txt")
        timeFile   = os.path.join(algoDir, f"{baseName}_time.txt")
        testFile   = os.path.join(algoDir, f"{baseName}_test.txt")

        print(f"Running on {baseName}... ", end="", flush=True)
        startTime = time.time()

        try:
            subprocess.run([
                executable,
                str(algoId),
                inputFile,
                outputFile,
                timeFile,
                testFile
            ], check=True, stdout=subprocess.DEVNULL, stderr=subprocess.PIPE)
            print(f"Done ({(time.time() - startTime):.2f}s)")
        except subprocess.CalledProcessError as e:
            print(f"Failed!\n{e.stderr.decode('utf-8', errors='ignore')}")
