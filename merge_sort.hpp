/**
 * @author: Raghu Sai Phani Sriraj Vemparala
 * @file  : merge_sort.hpp
 * @brief : This file contains the class and function declarations required for merge sort operation.
 * Date   : 06 september 2023
*/
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;

class ms
{
private:
    vector<int> v1;
public:
/**
 * Merges two unsorted arrays
 * 
 * @param v1 Vector of integers to be sorted
 * @param low lower index of the vector array
 * @param mid mid index of the vector array
 * @param high higher index of the vector array
 */
    void merge(int , int , int );

/**
 * Implements the merge sort algorithm
 * 
 * @param v1 Vector of integers to be sorted
 * @param low lower index of the vector array
 * @param high higher index of the vector array
 */
    void merge_sort(int , int );

/**
 * Returns the vector length
 * 
 */
    int vector_length();

/**
 * Push Data to vector
 * 
 */
    void pushdatatovector(const std::string& );

/**
 * Write Data to vector
 * 
 */
    void outputtofile(const std::string& );

/**
 * Print vector
 * 
 */
    void print_vector();
};