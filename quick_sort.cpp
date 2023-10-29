/**
 * @author: Raghu Sai Phani Sriraj Vemparala
 * @file  : quick_sort.cpp
 * @brief : This file contains the functions required for quick sort operation.
 * Date   : 06 september 2023
*/
#include "quick_sort.hpp"

/**
 * Swaps two integers using XOR
 * 
 * @param a First integer pointer
 * @param b Second integer pointer
 */
void qs::swap(int *a, int *b)
{
    if(a == b)
    {
        return;//If the addresses are same return
    }
    *a = *a ^ *b;
    *b = *a ^ *b;
    *a = *a ^ *b;
}

/**
 * Finds the pivot for the quicksort algorithm
 * 
 * @param v1 Vector of integers to be sorted
 * @param low lower index of the vector array
 * @param high higher index of the vector array
 * @return Index of the pivot
 */
int qs::find_pivot(vector<int>& v1, int low, int high) 
{
    
    int i = low;
    int pivot = v1[high];
    for (int j = low; j < high; j++)
    {
        // Segregates such that the values lower than pivot comes to the left side of the pivot.
        if (v1[j] < pivot)
        {
            swap(&v1[i], &v1[j]);
            i++;
        }
    }

    swap(&v1[i], &v1[high]);
    return i;// returning the pivot value
}

/**
 * Implements the quicksort algorithm
 * 
 * @param v1 Vector of integers to be sorted
 * @param low lower index of the vector array
 * @param high higher index of the vector array
 */
void qs::quick_sort(vector<int>&v1, int low, int high)
{    
    if(low<high)
    {
        int pivot = find_pivot(v1, low, high);
        quick_sort(v1,low,pivot-1); // Recursive function for quick_sort
        quick_sort(v1, pivot+1, high);   
    }
}
