// Import needed standard library.
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <chrono>

// Import needed headers and cpp source files.
#include "./headers/HeapSort.h"
#include "./headers/MergeSort.h"
#include "./headers/QuickSort.h"
#include "./headers/StdSort.h"
#include "tools.cpp"

// Define constants.
#define DATASETS_PATH "../datasets"
#define TEST_SIZE 1000000
#define LOOP_TIMES 10

// Entry point.
int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

                // Check the the operating system to select the right python execute command.
    std::string pythonExecuteCommand = (thisOS() == "Linux") ? "python3" : "python",

                // Declare 3 commands that will be call to execute needed python script.
                command1 = pythonExecuteCommand + " generate_data.py" + " --datasetspath " + DATASETS_PATH
                                                + " --testsize " + std::to_string(TEST_SIZE),
                command2 = pythonExecuteCommand + " validate_result.py" + " --datasetspath " + DATASETS_PATH,
                command3 = pythonExecuteCommand + " visualize_result.py" + " --datasetspath " + DATASETS_PATH;

    // Run python script to organize folder, generate and save testsets.
    system(command1.c_str());

    // Create 2D vectors for storing the runtime of each algorithm and storing all testsets.
    std::vector<std::vector<float>> results(4), testSets = loadTestSets(DATASETS_PATH);

    // Save the testsets after being sorted by each algorithm for validating.
    saveResult(HeapSort,  testSets, DATASETS_PATH, "heapsort");
    saveResult(MergeSort, testSets, DATASETS_PATH, "mergesort");
    saveResult(QuickSort, testSets, DATASETS_PATH, "quicksort");

    // Run python script to validate the result of each algorithm and print on the screen
    system(command2.c_str());

    // Loop over 10 tests, apply the sorting algorithms a number of time on the copy of the test 
    // (to not change the original test) and save the average runtime of each algorithm.
    for (const std::vector<float>& test: testSets)
    {
        // Calculate average runtime.
        float avgHeapSortRunTime  = timeIt(HeapSort,  test, LOOP_TIMES),
              avgMergeSortRunTime = timeIt(MergeSort, test, LOOP_TIMES),
              avgQuickSortRunTime = timeIt(QuickSort, test, LOOP_TIMES),
              avgStdSortRunTime   = timeIt(StdSort,   test, LOOP_TIMES);

        // Save results.
        results[0].push_back(avgHeapSortRunTime);
        results[1].push_back(avgMergeSortRunTime);
        results[2].push_back(avgQuickSortRunTime);
        results[3].push_back(avgStdSortRunTime);
    }

    // Export the result to .csv file.
    exportCsv(results, DATASETS_PATH);

    // Run python script to show line chart and save it as .jpg file.
    system(command3.c_str());
    
    // End of programme.
    return 0;
}
