#ifndef __P1_PROCESS
#define __P1_PROCESS

#include <fstream>
#include <iostream>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <vector>
//For wiating for all the threads from the main thread
#include <sys/types.h>
#include <sys/wait.h>

#include "p1_threads.h"
#include "student.h"

struct thread_args
{
	int num_threads;
	int threadNum;
	int sizeofVector;
	int remainder;
	std::vector<student> *sV;
};

void get_statistics(std::string class_name[], int num_processes, int num_threads, int num_files);

std::vector<student> getStudents(std::string class_name);

double mean(std::vector<student> students, int begin, int end);
double standardDeiviation(std::vector<student> students, int begin, int end);
double median(std::vector<student> students, int begin, int end);

void writeToFile(std::vector<student> stud, std::string class_name);
#endif
