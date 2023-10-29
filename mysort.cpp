/**
 * @author: Raghu Sai Phani Sriraj Vemparala
 * @file  : mysort.cpp
 * @brief : This file contains the main function and parsing of parameters is performed.
 * @References: https://stackoverflow.com/questions/8793020/using-getopt-long-c-how-do-i-code-up-a-long-short-option-to-both-require-a
 *              https://linux.die.net/man/3/getopt_long
 *              https://www.geeksforgeeks.org/merge-sort/
 *              https://www.geeksforgeeks.org/quick-sort/
 *              
 * Date   : 21 september 2023
*/
#include <iostream>
#include <vector>
#include <getopt.h>
#include <fstream>
#include <string>
#include "sort_thread.hpp"
using namespace std;

size_t thread_count = 4;

bs bk_sort;
ms mg_sort;

int main(int argc,char* argv[]) 
{
    std::vector<int> v1;
    int c = 0, option_index =0;
    string my_name, input_file, output_file, algorithm;
    //structure for options to be parsed and validate
    static struct option long_options[] = {
            {"name",    no_argument, 0,  'n' },
            {"inputfile",  required_argument,       0,  'i' },
            {"outputfile",  required_argument, 0,  'o' },
            {"total_threads",  optional_argument, 0,  't' },
            {"alg", required_argument,       0,  'a' },
            {0,         0,                 0,  0 }
            };
    while (1) 
    {
        //passing arguments for further operation
        c = getopt_long(argc, argv, "ni:o:t:a:", long_options, &option_index);
        if (c == -1)
            break;
        //Switch case is used to store the arguments
       switch (c) 
       {
            case 'n':
                cout << "Raghu Sai Phani Sriraj Vemparala" << endl;
                return 0;
                break;
            case 'i':
                input_file = std::string(optarg);
                break;
            case 'o':
                output_file  = std::string(optarg);
                break;
            case 't':
                thread_count = atoi(optarg);
                if(thread_count > 150)
                {
			        printf("ERROR; too many threads\n");
			        return 1;
                }
                //cout << "Thread count:" << thread_count<<endl;
                break;
            case 'a':
                algorithm = std::string(optarg);
                cout <<algorithm <<endl;
                break;
            default: 
                cout << "Invalid_argument" <<endl;
                break;
       }
    }
    //open an input file
    ifstream inputfile(input_file);
    if(inputfile.is_open())
    {
        if(algorithm == "forkjoin")
        {
            mg_sort.pushdatatovector(input_file);
        }
        else if(algorithm == "lkbucket")
        {
            //cout << "Ent lkbucket";
            bk_sort.pushdatatovector(input_file);
        }
    }
    else
    {
        cout << "Failed to open input file" <<endl;
        return -1;
    }
    inputfile.close();
    //open output file or create a file
    ofstream outputfile(output_file);
    if(outputfile.is_open())
    {
        //check for the algorithm
        if(algorithm =="forkjoin")
        {
            sort_thread_init(mg_sort);
            mg_sort.outputtofile(output_file);
        }
        else if(algorithm == "lkbucket")
        {
            bucket_thread_init(bk_sort);
            bk_sort.outputtofile(output_file);
        }
        else
        {
            cout << "Invalid_Algorithm" <<endl;
            return 0;
        }
        //push the data to the output file
        
    }
    else
    {
        cout << "Failed to open output file" << endl;
        return -1;
    }
    //close the output file
    outputfile.close();
    return 0;   
}