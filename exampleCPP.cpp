#include <barrier>
#include <iostream>
#include <string>
#include <thread>
#include <vector>
#include <ctime>
#include "quick_sort.hpp"
#include "merge_sort.hpp"

using namespace std;

vector<thread*> threads;
size_t NUM_THREADS;

/*
Note that the barrier requires C++20 (use flag --std=c++2a)  
If you don't have access to C++20 on your local machine,
you'll get a #include <barrier> no such file error on compilation.
Jupyter does have C++20 installed.

Note that you can always use a pthread barrier instead, even in C++.
just #include<pthread> and see the C example for usage.
*/
barrier<> *bar; 
mutex* lk;
ms mergesort;
struct timespec startTime, endTime;

void global_init(){
	bar = new barrier(NUM_THREADS);
	lk = new mutex();
}

void global_cleanup(){
	delete bar;
	delete lk;
}
vector<int> v1 = {16,
9,
14,
6,
10,
3,
13,
15,
11,
18};
void local_init(){}
void local_cleanup(){}

void* thread_main(size_t tid)
{
	int length = v1.size();
	printf("length is :%d\n",length);

	local_init();
	bar->arrive_and_wait();
	if(tid==0){
		clock_gettime(CLOCK_MONOTONIC,&startTime);
	}
	bar->arrive_and_wait();
	int low = (int)((tid) * length) / NUM_THREADS;
	int high = (int)(((tid+1)*length) / NUM_THREADS) - 1;
	mergesort.merge_sort(v1,low,high);
	// do something
	//printf("Thread %zu reporting for duty\n",tid);
	//lk->lock();
	//printf("Thread %zu got the lock!\n",tid);
	//lk->unlock();

	bar->arrive_and_wait();

	if(tid==0){
		clock_gettime(CLOCK_MONOTONIC,&endTime);
	}

	local_cleanup();
	
	return 0;
}

void final_merge(int nt)
{
	int i = 0;
	int length = v1.size();
	int low  = 0;
	for(int i = 0; i<nt-1; i++)
	{
		int mid = (int)((i+1) * length)/NUM_THREADS -1 ;
		int high = (int)((i+2) * length)/NUM_THREADS - 1;
		mergesort.merge(v1, low, mid, high);
	}	
}

int main(int argc, const char* argv[])
{
	int length = v1.size();
	// parse args
	if(argc==2){
		NUM_THREADS = atoi( argv[1] );
		if(NUM_THREADS > 150){
			printf("ERROR; too many threads\n");
			exit(-1);
		}
	}
	else
	{
		NUM_THREADS = 4;
	}
	
	
	global_init();
	
	// launch threads
	int ret; size_t i;
	threads.resize(NUM_THREADS);
	for(i=1; i<NUM_THREADS; i++){
	 	threads[i] = new thread(thread_main,i);
	 }
	i = 0;
	thread_main(i); // master also calls thread_main
	
	// join threads
	for(size_t i=1; i<NUM_THREADS; i++){
		threads[i]->join();
		printf("joined thread %zu\n",i);
		delete threads[i];
	}
	for(int i = 0;i < length;i++)
	{
		cout<<v1[i]<<endl;
	}
	//final_merge(NUM_THREADS);
	printf("Final_Merge_done\n");
	for(int i = 0;i <length;i++)
	{
		cout<<v1[i]<<endl;
	}
	global_cleanup();
	
	unsigned long long elapsed_ns;
	elapsed_ns = (endTime.tv_sec-startTime.tv_sec)*1000000000 + (endTime.tv_nsec-startTime.tv_nsec);
	printf("Elapsed (ns): %llu\n",elapsed_ns);
	double elapsed_s = ((double)elapsed_ns)/1000000000.0;
	printf("Elapsed (s): %lf\n",elapsed_s);
}