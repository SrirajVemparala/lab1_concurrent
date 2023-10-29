/**
 * @author: Raghu Sai Phani Sriraj Vemparala
 * @file  : sort_thread.cpp
 * @brief : This file contains the functions related to thread creation and initialization is performed.
 * 
 *              
 * Date   : 21 september 2023
*/

#include <iostream>
#include <cmath>
#include <string>
#include <thread>
#include <vector>
#include <ctime>
#include <mutex>
#include <barrier>
#include <algorithm>
#include "sort_thread.hpp"

using namespace std;

//Thread vector pointer
vector<thread*> threads;
//Start time and end time
struct timespec startTime, endTime;


/*
Note that the barrier requires C++20 (use flag --std=c++2a)  
If you don't have access to C++20 on your local machine,
you'll get a #include <barrier> no such file error on compilation.
Jupyter does have C++20 installed.

Note that you can always use a pthread barrier instead, even in C++.
just #include<pthread> and see the C example for usage.
*/
barrier<> *bar; 
std::vector<std::mutex>* lk;

extern size_t thread_count;

/**
 *this function initializes the barriers and locks
 * 
 */
void global_init(){
	bar = new barrier(thread_count);
	lk  = new std::vector<std::mutex>(thread_count);
}
/**
 *this function deletes the barriers and locks initialized
 * 
 */
void global_cleanup(){
	delete bar;
	delete lk;
}

/**
 *this thread function calls merge sort function
 * 
 * @param tid Thread ID
 * @param mssort passes refernce to the ms class object
 */
void* thread_sort(size_t tid, ms &sort)
{
	int length = sort.vector_length();

	if(tid==0)
    {
		clock_gettime(CLOCK_MONOTONIC,&startTime);
	}
	// Waiting for all the threads to start at the same time.
	bar->arrive_and_wait();
	// Calculating low and high indices of the divided array.
	int low = (int)((tid) * length) / thread_count;
	int high = (int)(((tid+1)*length) / thread_count) - 1;
	//Calling merge_sort function
	sort.merge_sort(low,high);
	
	return 0;
}
/**
 *This thread function provides bucket_sort algorithm funcitonality
 * 
 * @param tid Thread ID
 * @param mssort passes refernce to the ms class object
 */
void* bucket_sort(int tid, bs& bk_sort, std::vector<vector<int>> &buckets, int bucket_count)
{
	int length = bk_sort.vector_length();
	if(tid==0)
    {
		clock_gettime(CLOCK_MONOTONIC,&startTime);
	}
	bar->arrive_and_wait();// Wait for the barrier
	//low index
	int low = (int)((tid) * length) / thread_count;
	// High Index
	int high = (int)((((tid+1)*length) / thread_count) - 1);
	int i = low;
    int j = 0;
	//Every thread loops its own part of the array
    		for(i = low;i <= high;i++)
    		{
                for(j = 0; j<bucket_count; j++)
                {
                        if(bk_sort.v1[i] > bk_sort.mins[j] && bk_sort.v1[i] <= bk_sort.mins[j+1])
                        {
							//Locking the bucket since only one thread should access the particular bucket
							(*lk)[j].lock();
                            buckets[j].push_back(bk_sort.v1[i]);
							(*lk)[j].unlock();
                            break;
                        }
                }
            }
	bar->arrive_and_wait();
	//Since my bucket_size is equal to number of threads, sorting the array
    std::sort(buckets[tid].begin(), buckets[tid].end());
	return 0;
}

/**
 *this function initializes the threads for merge sort functionality.
 * 
 *
 * @param mssort passes refernce to the ms class object
 */
void sort_thread_init(ms &sort)
{
    global_init();
	
	// launch threads
	int ret; size_t i;
	threads.resize(thread_count);
	//Spawning the threads
	for(i=1; i<thread_count; i++){
	 	threads[i] = new thread(thread_sort,i,std::ref(sort));
	 }
	i = 0;
	thread_sort(i,sort); // master also calls thread_sort

	// join threads
	for(size_t i=1; i<thread_count; i++)
    {
		threads[i]->join();
		//printf("joined thread %zu\n",i);
		delete threads[i];
	}
	clock_gettime(CLOCK_MONOTONIC,&endTime);
	//Merges the final unmerged thread
	final_merge(sort);
	//Calculate end time
	
	//Cleaning up the threads, mutexes
	global_cleanup();
	
	//Calculating the tootal time the thread ran
	unsigned long long elapsed_ns;
	elapsed_ns = (endTime.tv_sec-startTime.tv_sec)*1000000000 + (endTime.tv_nsec-startTime.tv_nsec);
	printf("Elapsed (ns): %llu\n",elapsed_ns);
	double elapsed_s = ((double)elapsed_ns)/1000000000.0;
	printf("Elapsed (s): %lf\n",elapsed_s);	
}

/**
 *this function initializes the threads for the bucket_sort fucntionality.
 * 
 *
 * @param bssort passes refernce to the ms class object
 */
void bucket_thread_init(bs &bk_sort)
{
	int bucket_count = thread_count;
	global_init();

    size_t i;
	std::vector<vector<int>> buckets(bucket_count); //buckets(bucket_count);
	int min_ele = bk_sort.min_element();
    int max_ele = bk_sort.max_element();
    //Creating range based on thread count
    int range = (max_ele-min_ele)/thread_count +1;
	threads.resize(thread_count);
	//Setting minimum count to push the data into each bucket
	bk_sort.find_min_elements(bucket_count, range,max_ele);
    //Creating threads
	for(i=1; i<thread_count; i++){
	 	threads[i] = new std::thread([i, &bk_sort, &buckets,bucket_count]() { bucket_sort(i, bk_sort, buckets,bucket_count); });
	}
	i = 0;
    // Main thread calling bucket_sort
	bucket_sort(i, std::ref(bk_sort), buckets, bucket_count); // master also calls bucket_sort
	// join threads
	for(size_t i=1; i<thread_count; i++)
    {
		threads[i]->join();
		//printf("joined thread %zu\n",i);
		delete threads[i];
	}
	clock_gettime(CLOCK_MONOTONIC,&endTime);
    global_cleanup();
	//Clear the initial vector data
	bk_sort.clear_vector();
    //Storing the data in the result
	bk_sort.write_data(buckets, bucket_count);
	//Calculating the total time taken to run the thread
	unsigned long long elapsed_ns;
	elapsed_ns = (endTime.tv_sec-startTime.tv_sec)*1000000000 + (endTime.tv_nsec-startTime.tv_nsec);
	printf("Elapsed (ns): %llu\n",elapsed_ns);
	double elapsed_s = ((double)elapsed_ns)/1000000000.0;
	printf("Elapsed (s): %lf\n",elapsed_s);	
}

/**
 *this function merges the final list of sorted arrays
 * 
 *
 * @param ms &sort: passes refernce to the ms class object
 */
void final_merge(ms &sort)
{
	int i = 0;
	int length = sort.vector_length();
	int low  = 0;
	//Looping through the final sorted merged arrays

	for(int i = 0; i<thread_count-1; i++)
	{
		int mid = (int)(((i+1) * length)/thread_count) -1 ;
		int high = (int)(((i+2) * length)/thread_count) - 1;
		sort.merge(low, mid, high);
	}
}