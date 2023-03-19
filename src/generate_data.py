import os
import numpy as np
from tqdm import tqdm
import argparse



# parse arguments
parser = argparse.ArgumentParser()
parser.add_argument("--datasetspath", type=str)
parser.add_argument("--testsize", type=int)
args = parser.parse_args()

# define constant
DATASETS_PATH = args.datasetspath
TEST_SIZE = args.testsize

# list all directories in a directory
def listDir(path):
    return sorted(os.listdir(path), key=lambda x: os.path.getctime(os.path.join(path, x)))


# set up the path 
def setUpDatasetsPath():
    generatedTests = listDir(DATASETS_PATH)
    lastTestIdx = int(generatedTests[-1].replace("test", "")) if len(generatedTests) != 0 else 0
    os.makedirs(f"{DATASETS_PATH}/test{lastTestIdx + 1}/testsets/unsorted")
    os.makedirs(f"{DATASETS_PATH}/test{lastTestIdx + 1}/testsets/sorted")
    os.makedirs(f"{DATASETS_PATH}/test{lastTestIdx + 1}/results/heapsort")
    os.makedirs(f"{DATASETS_PATH}/test{lastTestIdx + 1}/results/mergesort")
    os.makedirs(f"{DATASETS_PATH}/test{lastTestIdx + 1}/results/quicksort")


# generate testsets
def testSetGenerate():
    currTest = listDir(DATASETS_PATH)[-1]
    unsortedTestDes = f"{DATASETS_PATH}/{currTest}/testsets/unsorted"
    sortedTestDes = f"{DATASETS_PATH}/{currTest}/testsets/sorted"
    print(f"\n{currTest}:\ngenerating data...")
    for i in tqdm(range(10)):
        test = np.random.rand(TEST_SIZE)
        sortedTest = sorted(test)
        if (i == 0):
            testName = "ascending.txt"
            test = sorted(test)
        elif (i == 1):
            testName = "descending.txt"
            test = sorted(test, reverse=True)
        else:
            testName = f"random{i - 1}.txt"

        with open(f"{unsortedTestDes}/{testName}", "w") as f:
            for num in test:
                f.write("{:.6f}".format(num))
                f.write('\n')

        with open(f"{sortedTestDes}/{testName}", "w") as f:
            for num in sortedTest:
                f.write("{:.6f}".format(num))
                f.write('\n')


if __name__ == "__main__":
    setUpDatasetsPath()
    testSetGenerate()