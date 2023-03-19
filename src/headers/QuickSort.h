#pragma once
#include <random>
#include <vector>


void QuickSort(std::vector<float>&);
void quickSortHeper(std::vector<float>&, int, int);

// Quick sort with random pivot selecting strategy
void QuickSort(std::vector<float>& arr)
{
    quickSortHeper(arr, 0, arr.size() - 1);
}

// Recursive function
void quickSortHeper(std::vector<float>& arr, int left, int right)
{
    // Set up two traversing pointer
    int pLeft = left, pRight = right;
    
    // Set the pivot to be a random value in range [left, right] of the array
    float pivot = arr[left + rand() % (right - left)];

    // Sort that all the element which is less than or equal to pivot placed
    // on the left side of the array (partition)
    while (pLeft < pRight)
    {
        // Traverse the left pointer from the left to the right, find the element that is larger than pivot
        while (arr[pLeft] < pivot) ++pLeft;
        // Traverse the right pointer from the right to the left, find the element that is less than pivot
        while (arr[pRight] > pivot) --pRight;

        // If two traversing pointers are not go through each other yet, swap two elements at their positions and continue searching
        if (pLeft <= pRight)
        {
            std::swap(arr[pLeft], arr[pRight]);
            ++pLeft;
            --pRight;
        }
    }

    // Recursively call the function and perform partition on two part (one less than pivot and one larger than pivot)
    if (left < pRight) quickSortHeper(arr, left, pRight);
    if (pLeft < right) quickSortHeper(arr, pLeft, right);
}

