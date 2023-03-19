#pragma once
#include <vector>


void MergeSort(std::vector<float>&);
void merge(std::vector<float>&, int, int, int, int);

// Recursive aproaching merge sort
void MergeSort(std::vector<float>& arr)
{
    int end = arr.size() - 1;
    merge(arr, 0, end/2, end/2 + 1, end);
}

// Recursive function
void merge(std::vector<float>& arr, int start1, int end1, int start2, int end2)
{
    // If the function doesnt reach the base case, continue call it recursively
    if (start1 != end1) 
        merge(arr, start1, (start1 + end1) / 2, (start1 + end1) / 2 + 1, end1);
    
    if (start2 != end2)
        merge(arr, start2, (start2 + end2) / 2, (start2 + end2) / 2 + 1, end2);
    
    int iter1 = 0, iter2 = 0,
        size1 = end1 - start1 + 1,
        size2 = end2 - start2 + 1;

    // Create two temporary arrays to store 2 part of the array that is going to be merged
    float run1[size1], run2[size2];

    for (int i = start1; i <= end1; ++i)
        run1[i - start1] = arr[i];

    for (int i = start2; i <= end2; ++i)
        run2[i - start2] = arr[i];

    // Merge 2 part of the array
    for (int i = start1; i <= end2; ++i)
    {
        if ((iter1 < size1) && (iter2 >= size2 || run1[iter1] <= run2[iter2]))
        {
            arr[i] = run1[iter1];
            ++iter1;
        }
        else
        {
            arr[i] = run2[iter2];
            ++iter2;
        }
    }
}

