
# Description of code organization:

## There are 6 files for the code development. They are:
</br>1. mysort.cpp</br>
</br>2. bucket_sort.hpp</br>
</br>3. bucket_sort.cpp</br>
</br>4. merge_sort.hpp</br>
</br>5. merge_sort.cpp</br>
</br>6. sort_thread.cpp</br>
</br>7. sort_thread.hpp</br>
</br>6. Makefile</br>

## Contents in each file:

**1. mysort.cpp:** This file has the main function. The following are the fucntionalities.<br>
&nbsp;&nbsp;a. The parsing functionality is implemented.<br>
&nbsp;&nbsp;b. Data is collected from input file and pushed into the array.<br>
&nbsp;&nbsp;c. Output file is created and the final sorted data is pushed into the output file.<br>
&nbsp;&nbsp;d. Bucket sort and merge sort class objects are created.<br>
&nbsp;&nbsp;e. Calls are made to the sorting algorithms.<br>

**2. bucket_sort.hpp:**  This file contains the class declaration and function declarations for the bucket_sort.</br>
&nbsp;The following class and function declarations are present:<br>
&nbsp;&nbsp;a. class name: bs<br>
&nbsp;&nbsp;&nbsp;Public Functions:<br>
&nbsp;&nbsp;b.vector_length(): This function provides length of the vector array.<br>
&nbsp;&nbsp;c.min_element(): This function provides minimum element of the vector array.<br>
&nbsp;&nbsp;d.max_element(): This function provides maximum element of the vector array.<br>
&nbsp;&nbsp;e.find_min_elements(): This function provides minimum length of the elements for each bucket.<br>
&nbsp;&nbsp;f.clear_vector(): This function clears the vector array.<br>
&nbsp;&nbsp;g.write_data():This function writes data of each bucket into the vector array.<br>
&nbsp;&nbsp;h.pushdatatovector(): This function takes the input path of the input file and pushes data into the vector from the file.<br>
&nbsp;&nbsp;i.outputtofile(): This function takes the output file path of the output file and pushes data from the vector into the file.<br>
&nbsp;&nbsp;j.print_vector(): This function takes the prints the vector of the file.<br>
&nbsp;&nbsp;&nbsp;Public variables:<br>
&nbsp;&nbsp;i.v1: Vector array to store the input data of the file.<br>
&nbsp;&nbsp;j.mins: Vector array to store minimum values of each bucket.<br>


**3. bucket_sort.cpp :** This file contains the class function definitions for the bucket_sort file.<br>
&nbsp;The following function definitions are present:<br>
&nbsp;&nbsp;a. class name: bs<br>
&nbsp;&nbsp;&nbsp;Public Functions:<br>
&nbsp;&nbsp;b.vector_length(): This function provides length of the vector array.<br>
&nbsp;&nbsp;c.min_element(): This function provides minimum element of the vector array.<br>
&nbsp;&nbsp;d.max_element(): This function provides maximum element of the vector array.<br>
&nbsp;&nbsp;e.find_min_elements(): This function provides minimum length of the elements for each bucket.<br>
&nbsp;&nbsp;f.clear_vector(): This function clears the vector array.<br>
&nbsp;&nbsp;g.write_data():This function writes data of each bucket into the vector array.<br>
&nbsp;&nbsp;h.pushdatatovector(): This function takes the input path of the input file and pushes data into the vector from the file.<br>
&nbsp;&nbsp;i.outputtofile(): This function takes the output file path of the output file and pushes data from the vector into the file.<br>
&nbsp;&nbsp;j.print_vector(): This function takes the prints the vector of the file.<br>
&nbsp;&nbsp;&nbsp;Public variables:<br>
&nbsp;&nbsp;i.v1: Vector array to store the input data of the file.<br>
&nbsp;&nbsp;j.mins: Vector array to store minimum values of each bucket.<br>

### Functionality of Multithreading Bucket sort:<br>
&nbsp;The Bucket sort algorithm follows the below steps:<br>
&nbsp;&nbsp;a. We start the algorithm by divding the array into sub-arrays and thereby assigning each part of the array to the respective thread.  <br>
&nbsp;&nbsp;Each thread takes its own high and low indexes.<br>
&nbsp;&nbsp;b. Based of the maximum and minimum value of the vector array a range is calculated and the based on the bucket count, bucket_count+1 length of min values are considered.<br>
&nbsp;&nbsp;c. By default the the thread count is equal to the bucket count.<br>
&nbsp;&nbsp;d. Based on the number of threads the total locks are considered. If there are 4 threads that means there are 4 locks. Each lock gaurds each bucket.<br>
&nbsp;&nbsp;e. Once the element is read and it falls in the min range of that bucket. It is pushed into that bucket.<br>
&nbsp;&nbsp;f. Once all the buckets are filled then they are sorted and stored into the vector.<br>

**4. merge_Sort.hpp**: This file contains the class declaration and function declarations for the merge_sort file.<br> 
&nbsp;&nbsp;The following class and function declarations are present:<br>
&nbsp;&nbsp;a. class name: ms<br>
&nbsp;&nbsp;&nbsp;Public Functions:<br>
&nbsp;&nbsp;b. merge(): Used for sorting the array and merging the vector array.<br>
&nbsp;&nbsp;c. merge_sort(): Used for dividing the array into two equal parts.<br>

**5. merge_Sort.cpp:** This file contains the class declaration and function declarations for the merge_sort file.<br>
&nbsp;The following function defintions are present: <br>
&nbsp;&nbsp;a. merge()<br>
&nbsp;&nbsp;b. merge_sort()<br>

### Functionality of Multithreading Merge sort:<br>
&nbsp;The merge sort algorithm follows the below steps:<br>
&nbsp;&nbsp;a. Each thread takes a sub-array based on the thread. <br>
&nbsp;&nbsp;b. Each thread calls merge_sort() algorithm and performs merge sort and we get the merged result of each sub-array.<br>
&nbsp;&nbsp;c. Once each sub-array is sorted then final merging of each sub-array is performed.<br>

**6. sort_thread.cpp:** This file contains function definitons of thread intialization and bucket_sort algorithm.<br>
&nbsp;&nbsp;The following class and function definitions are present:<br>
&nbsp;&nbsp;a. global_init() - Initializes barries and mutexes.<br>
&nbsp;&nbsp;b. global_cleanup() -Deletes the barrier and the mutex.<br>
&nbsp;&nbsp;c. thread_sort() -this thread function calls merge sort function.<br>
&nbsp;&nbsp;d. bucket_sort() - this thread function provides bucket_sort algorithm funcitonalityt.<br>
&nbsp;&nbsp;e. sort_thread_init() - this function initializes the threads for merge sort functionality.<br>
&nbsp;&nbsp;f. bucket_thread_init() - this function initializes the threads for the bucket_sort fucntionality.<br>
&nbsp;&nbsp;g. final_merge() - this function merges the final list of sorted arrays in merge sort.<br>

**7. sort_thread.hpp:** The following operations can be performed using the MakeFile.<br>
&nbsp;&nbsp;a. global_init()<br>
&nbsp;&nbsp;b. global_cleanup()<br>
&nbsp;&nbsp;c. thread_sort()<br>
&nbsp;&nbsp;d. bucket_sort()<br>
&nbsp;&nbsp;e. sort_thread_init()<br>
&nbsp;&nbsp;f. bucket_thread_init()<br>
&nbsp;&nbsp;g. final_merge()<br>


**8. Makefile:** The following operations can be performed using the MakeFile.<br>
&nbsp;&nbsp;a. make clean - clean the -o files and bin files.<br>
&nbsp;&nbsp;b. make - Generates a executable with name mysort.<br>

# Description of Parallelization Strategy

* Merge_sort:
    * The parallelization strategy used is to seperate the threads into equal parts based on the number of threads and merge the final array. 
    * A formualae was deviced to seperate the array into equal parts. 
    * The number of parts the array is divided is proportional to the thread count and the length of the array. 
    * Each thread is allocated an array and then the merge sort is performed by individual thread on the individual array. 
    * Once the individual arrays are sorted using the merge sort algorithm then the threads are joined and after that the individual arrays are compared and merged together.
* Bucket_sort:
    * The bucket sort algorithm uses locking strategy. 
    * The array is divided into equal parts based on the number of threads . 
    * Each thread runs takes its own index of the sub -arrays created and then it stores the data into the bucket based on the minimum value that can be pushed into the bucket.
    * In my algorithm the number of buckets is equal to the number of total number of threads. Locking strategy is used to store the data into the bucket.

# Performance

* It was observed that the performance of bucket sort algorithm is better than merge sort algorithm.The following are the observations:
    * Large data sets:
        1. By comparing equal array size of bucket sort and merge sort for the example 550000in1-1000000.txt it was observed that bucket sort was more efficient than merge sort algorithm.
        2. It was also observed that the time taken for the merge sort algorithm increases for every increase of the thread count.
      Performance impact of thread count in merge sort:
        3. The merge sort algorithm was taking more time for increase in threads. The above mentioned test set was tested with both 50 and 100 threads and the time increased because each thread should handle smaller chunks of data.<br>
      Performance impact of thread count in bucket sort:<br>  
        4. I have observed that lkbucket took a lot of time when it ran at 50 threads and it took less time as the threads reached 100 for the array with 6200000in1-10000000.txt. I think that this performance increase was due to taking the buckets count is equal to the thread count and also using locks for each bucket seperately.
    * Small data sets:
        1. The performance of merge sort was better when the data set was smaller.  The reason for this is that my algorithm has thread count equal to bucket count due to which the distribution of data into buckets has effected the timing. On other hand since the data is evenly spread among 4 threads and algorithm has fixed time complexity it is showing better results.

        2. Effect of increasing the thread count:<br>
            The performance of bucket sort was better because in the merge sort algorithm as threads increases and when thread count is equal to the array length the performance is highly reduced since there is no multi threading that can be performed and each number should be merged seperately.

        3. Since I took locks_count = threads_count = buckets_count. It has provided the following advantages:<br>
            Balanced Workload: With the same number of threads, locks, and buckets, each thread is responsible for sorting a single bucket concurrently. This approach evenly distributes the workload among threads.<br>
            Efficient Parallelism: Each thread operates independently on its assigned sub-array without the need for complex synchronization mechanisms.<br>
            Reduced Overhead: Since there is no contenetion of locks on each bucket i.e each thread has its lock and bucket, Synchronisation overhead is minimized.<br>


    Overall, My lkbucket performed better than the forkjoin.<br>

## Extant Bugs:
&nbsp;No bugs were observed during the tests and autograde.sh was successful.<br>

