#include "p1_threads.h"

// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function
std::vector<student>* mergeSortThread(int begin, int end, std::vector<student>* studs)
{
	std::vector<student> b = *studs;
	std::vector<student>::iterator it;
	for(it = studs->begin(); it != studs->end(); it++)
	{
		b.push_back(*it);
	}
	split(&b, begin, end, studs);
	return studs;
}

void *runnable(void *param)
{
	//printf("Creating threads  \n");
	//getting arguments from param
	struct thread_args *threadArgs = (struct thread_args *)param;
	//std::cout << "sizeof vector is " << threadArgs->sizeofVector << std::endl;
	int begin = threadArgs->threadNum * threadArgs->sizeofVector;
	int end = (threadArgs->threadNum+1) * threadArgs->sizeofVector-1;
	mergeSortThread(begin, end, threadArgs->sV);
	//printf("")
	return NULL;
}	//creates thread

void split(std::vector<student> *D, int iBegin, int iEnd, std::vector<student> *C)
{
	int iMiddle = (iBegin + iEnd)/2;
	split(C, iBegin, iMiddle, D);
	split(C, iMiddle, iEnd, D);

}

void Merge(std::vector<student> *C, int begin, int middle, int end, std::vector<student> *D)
{
	int i = begin;
	int j = middle;
	for(int k = begin; k < end; k++)
	{
		if(i < middle && (j>=end || C->at(i).getScore() <= C->at(j).getScore()))
		{
			D->at(k) = C->at(i);
			i++;
		}
		else
		{
			D->at(k) = C->at(j);
			j++;
		}
	}
}
