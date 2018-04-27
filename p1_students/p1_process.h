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
	std::vector<student> *sV;
	int begin;
	int end;
};

void get_statistics(std::string class_name[], int num_processes, int num_threads, int num_files);

std::vector<student> getStudents(std::string class_name);

double mean(std::vector<student> students);
double standardDeiviation(std::vector<student> students);
double median(std::vector<student> students);

void writeToFile(std::vector<student> stud, std::string class_name);
void writeStatistics(std::vector<student> stud, std::string class_name, double mean, double median, double standardDeviation);
#endif
