import glob
import os
from collections import defaultdict

def main():
    timeFiles = glob.glob(os.path.join("results", "*", "*_time.txt"))
    
    if not timeFiles:
        print("No time files found in results/ directory. Please run the benchmark first.")
        return

    # Dictionary to track which sizes an algorithm beat std::sort
    # Format: { "AlgoName": [10, 100, 1000...] }
    surpassedSizes = defaultdict(list)

    for file in timeFiles:
        try:
            with open(file, 'r') as f:
                lines = [line.strip() for line in f if line.strip()]
            
            size = None
            algoName = None
            algoTime = None
            stdTime = None

            # Parse lines based on output format in sorting.cpp
            for line in lines:
                if line.startswith("Dataset size = "):
                    size = int(line.split("=")[1].strip())
                elif line.startswith("Time: "):
                    t = float(line.split()[1])
                    if algoTime is None:
                        algoTime = t
                    else:
                        stdTime = t
                elif line != "std::sort" and not line.startswith("Comparison:"):
                    # The first unrecognized string after size is usually the custom algo's name
                    if size is not None and algoTime is None:
                        algoName = line

            # If the algorithm executed faster than std::sort
            if algoTime is not None and stdTime is not None and algoName is not None:
                if algoTime < stdTime:
                    surpassedSizes[algoName].append(size)

        except Exception as e:
            print(f"Error parsing {file}: {e}")

    print(f"\n{'='*50}\nAlgorithms that Surpassed std::sort\n{'='*50}")
    if not surpassedSizes:
        print("No algorithms surpassed std::sort in any recorded tests.")
    else:
        for algo, sizes in surpassedSizes.items():
            sizes.sort()
            formattedSizes = ", ".join(format(s, ",") for s in sizes)
            print(f"-> {algo} won at dataset sizes: [{formattedSizes}]")
    print("="*50 + "\n")

if __name__ == "__main__":
    main()