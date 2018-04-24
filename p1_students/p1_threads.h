#ifndef __P1_THREADS
#define __P1_THREADS

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <pthread.h>

#include "p1_process.h"
#include "student.h"

void *runnable(void *param);//creates thread

std::vector<student>* mergeSortThread(int begin, int end, std::vector<student> studs);
#endif
