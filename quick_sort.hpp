/**
 * @author: Raghu Sai Phani Sriraj Vemparala
 * @file  : quick_sort.hpp
 * @brief : This file contains the class and function declarations required for quick sort operation.
 * Date   : 06 september 2023
*/
#include <iostream>
#include <vector>
using namespace std;

class qs
{
private:
/**
 * Swaps two integers using XOR
 * 
 * @param a First integer pointer
 * @param b Second integer pointer
 */
    void swap(int *, int *);

/**
 * Finds the pivot for the quicksort algorithm
 * 
 * @param v1 Vector of integers to be sorted
 * @param low lower index of the vector array
 * @param high higher index of the vector array
 * @return Index of the pivot
 */
    int find_pivot(vector<int>& , int , int );
public:
/**
 * Implements the quicksort algorithm
 * 
 * @param v1 Vector of integers to be sorted
 * @param low lower index of the vector array
 * @param high higher index of the vector array
 */
    void quick_sort(vector<int>&, int , int);
};