#pragma once
#include <vector>


void bubleDown(std::vector<float>&, int , int);
void HeapSort(std::vector<float>&);

// Iterative aproaching heap sort
void HeapSort(std::vector<float>& arr)
{
    int arrSize = arr.size();
    
    // Perform "bubble down" technique on each element in the first half of the array
    // (turn the array in to a max heap)
    for (int i = arrSize / 2 - 1; i >= 0; --i)
        bubleDown(arr, i, arrSize - 1); 

    // From the end of the array to the beginning: 
    // - bring to largest element to back (swap it with the last element)
    // - perform bubble down to turn the array to a max heap again
    for (int i = arrSize - 1; i >= 0; --i)
    {
        std::swap(arr[0], arr[i]);
        bubleDown(arr, 0, i - 1);
    }
}

// Non recursive function
void bubleDown(std::vector<float>& arr, int currIdx, int idxBound)
{
    while (true)
    {  
        // Temporary set curr element to be the largest among it and its children (left child, right child)
        int largestIdx = currIdx;
        // Indexes of left child and right child of the curr element
        int leftIdx = 2 * currIdx + 1;
        int rightIdx = 2 * currIdx + 2;

        // Find the largest among the curr element, left child and right child of it
        if (rightIdx <= idxBound && arr[rightIdx] > arr[largestIdx])
            largestIdx = rightIdx;

        if (leftIdx <= idxBound && arr[leftIdx] > arr[largestIdx])
            largestIdx = leftIdx;

        // If the curr element is already the largest among three of them, then stop bubble down
        if (largestIdx == currIdx)
            break;

        // If the curr element is less than one of its two child, swap it with the larger child
        // and continue perform bubble down until it is bigger that all of its two children
        std::swap(arr[currIdx], arr[largestIdx]);
        currIdx = largestIdx;
    }
}

