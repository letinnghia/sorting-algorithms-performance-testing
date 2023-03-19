import sys
import generate_data as gd
import argparse

parser = argparse.ArgumentParser()
parser.add_argument("--datasetspath", type=str)
args = parser.parse_args()

# declare constant
DATASETS_PATH = args.datasetspath
SORTING_ALGO = ["heapsort", "mergesort", "quicksort"]


# return true if the sorted output generate by each algorithm is equal to 
# the sorted testset alse return false
def validate(algo):
    currTest = gd.listDir(DATASETS_PATH)[-1]
    sortedTestSets = gd.listDir(f"{DATASETS_PATH}/{currTest}/testsets/sorted")
    results = gd.listDir(f"{DATASETS_PATH}/{currTest}/results/{algo}")

    if len(sortedTestSets) != len(results):
        print("Result saving error")
        return

    for i in range(len(sortedTestSets)):
        sortedTest = open(f"{DATASETS_PATH}/{currTest}/testsets/sorted/{sortedTestSets[i]}")
        result = open(f"{DATASETS_PATH}/{currTest}/results/{algo}/{results[i]}")
        return sortedTest.read() == result.read()
    
    return False


# loop through all algorithms, validate them and print the result to the screen
def validateResult():
    print("checking output...")
    for algo in SORTING_ALGO:
        print(f"{algo}: ", end="")
        if validate(algo):
            print("valid output")
        else:
            print("invalid output")
    
    print("calculating runtime...")


if __name__ == "__main__":
    sys.path.append("src/generate_data.py")
    validateResult()