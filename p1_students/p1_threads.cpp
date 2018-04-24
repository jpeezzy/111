#include "p1_threads.h"

// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function
std::vector<student>* mergeSortThread(int begin, int end, std::vector<student>* studs)
{
	/*for (int x = begin; x <= end; x++)
	{
		std::cout << "the score is " << studs->at(x).getScore() << std::endl;
	}*/
	return studs;
}

void *runnable(void *param)
{
	//printf("Creating threads  \n");
	//getting arguments from param
	struct thread_args *threadArgs = (struct thread_args *)param;
	//std::cout << "sizeof vector is " << threadArgs->sizeofVector << std::endl;
	int begin = threadArgs->threadNum * threadArgs->sizeofVector;
	int end = (threadArgs->threadNum+1) * threadArgs->sizeofVector;
	mergeSortThread(begin, end, threadArgs->sV);
	//printf("")
	return NULL;
}	//creates thread


