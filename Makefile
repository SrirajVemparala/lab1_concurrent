all: mysort

mysort: sort_thread.o merge_sort.o bucket_sort.o mysort.o
	g++ merge_sort.o sort_thread.o bucket_sort.o mysort.o -o mysort

merge_sort.o: merge_sort.cpp
	g++ -g -Wall -Werror -c merge_sort.cpp

bucket_sort.o: bucket_sort.cpp
	g++ -g -Wall -Werror -c bucket_sort.cpp

mysort.o: mysort.cpp
	g++ -g -Wall -Werror -c mysort.cpp

sort_thread.o: sort_thread.cpp
	g++ -g -c -pthread -O3 -std=c++2a sort_thread.cpp


.PHONY : clean
clean:
	rm -f sort_thread bucket_sort merge_sort mysort *.o
