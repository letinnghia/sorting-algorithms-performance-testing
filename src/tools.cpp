#include <chrono>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstring>
#include <dirent.h>
#include <iostream>
#include <functional>
#include <sys/utsname.h>

// Define constants.
const std::vector<std::string> algos {"Heap Sort", "Merge Sort", "Quick Sort", "std::sort"},
                               testNames {"ascending.txt", "descending.txt", "random1.txt", "random2.txt", "random3.txt",
                                            "random4.txt", "random5.txt", "random6.txt", "random7.txt", "random8.txt"};

// Argument function of std::sort for sorting folders.
bool strCmp(std::string s1, std::string s2)
{
    return (s1.length() == s2.length()) ? (s1 < s2) : (s1.length() < s2.length());
}

// Convert c-string (const char*) to std::string
std::string toString(const char*& cString)
{
    std::string stdString(cString);
    return stdString;
}

// Take in a sort function and a copy of a vector in testset, run the sort function n times and
// return the average time that the function runs (calculate the performance of sorting algorithm).
float timeIt(std::function<void(std::vector<float>&)> func, std::vector<float> arr, const int& loopTimes) 
{
    float totalDuration = 0.0;
    for (int i = 0; i < loopTimes; ++i)
    {
        std::vector<float> arrCopy = arr;
        auto start = std::chrono::high_resolution_clock::now();
        func(arrCopy);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
        totalDuration += duration.count();
    }
    
    return (float) (totalDuration / loopTimes);
}

// List all directories and files in a directory.
std::vector<std::string> listDirectory(const char* pathToDir)
{
    std::vector<std::string> dirs;
    DIR* dir = opendir(pathToDir);
    struct dirent* entry;
    
    if (dir != NULL) 
    {
        while ((entry = readdir(dir)) != NULL) 
            dirs.push_back(entry->d_name);
        closedir(dir);
    }
    else 
        std::cerr << "Error: could not open directory: " << pathToDir << std::endl;
    
    return dirs;
}

// Read the content of the test (.txt file) and return a vector.
std::vector<float> read(const std::string& filename)
{
    std::vector<float> content;
    std::ifstream infile(filename);
    if (infile.is_open()) 
    {
        std::string line;
        while (std::getline(infile, line)) 
        {
            std::istringstream iss(line);
            float value;
            while (iss >> value) 
            {
                content.push_back(value);
            }
        }
        infile.close();
    }
    return content;
}

// Return the curr test (latest test) in the datasets directory.
std::string getCurrTest(const char* datasetsPath)
{
    std::vector<std::string> dirs = listDirectory(datasetsPath);
    std::sort(dirs.begin(), dirs.end(), strCmp);
    std::string currTest = dirs.back();
    return currTest;
}

// Load 10 tests in to a single vector
std::vector<std::vector<float>> loadTestSets(const char* datasetsPath)
{
    std::vector<std::vector<float>> testSets;
    std::string currTest = getCurrTest(datasetsPath);
    std::string pathToTestSet = toString(datasetsPath) + "/" + currTest + "/" + "testsets" + "/" + "unsorted";
    std::vector<std::string> testNames = listDirectory(pathToTestSet.c_str());
    
    for (int i = 2; i < testNames.size(); ++i)
    {
        std::string filePath = pathToTestSet + "/" + testNames[i];
        testSets.push_back(read(filePath));
    }

    return testSets;
}

// Save the result of each algorithm to .txt file for validate the correctness of them.
void saveResult(std::function<void (std::vector<float>&)> func, const std::vector<std::vector<float>>& testSets, const char* datasetsPath, const std::string& algo) 
{
    std::string currTest = getCurrTest(datasetsPath);
    int i = 0;
    for (auto test: testSets)
    {
        func(test);

        std::string filePath = toString(datasetsPath) + "/" + currTest + "/" + "results" + "/" + algo + "/" + testNames[i];
        std::ofstream file(filePath, std::ios::app);

        for (float num : test) 
        {
            file << std::fixed << std::setprecision(6) << num << '\n';
        }

        file.close();
        ++i;
    }
}

// Export result (runtime of each algorithm) and save it as .csv file.
void exportCsv(const std::vector<std::vector<float>>& data, const std::string& datasetsPath) 
{
    std::string fileName = datasetsPath + "/" + getCurrTest(datasetsPath.c_str()) + "/" + "results" + "/" + "result.csv";
    std::ofstream outFile(fileName);


    int k = 0;
    outFile << ",";

    for (const auto& test: testNames)
        if (test == "random8.txt")
            outFile << test << "\n";
        else
            outFile << test << ",";

    for (const auto& row : data) 
    {
        outFile << algos[k] << ",";
        for (int i = 0; i < row.size(); ++i) 
        {
            if (i != row.size() - 1)
                outFile << row[i] << ",";
            else
                outFile << row[i] << "\n";
        }
        ++k;
    }
    outFile.close();
    std::cout << "results saved in " + datasetsPath + "/" + getCurrTest(datasetsPath.c_str()) + "/" + "results" << std::endl;
}

// Get the name of the current operating system where this programme is being executed.
std::string thisOS()
{
    struct utsname info;
    uname(&info);
    return info.sysname;
}

