#include "p1_threads.h"
#include <assert.h>
// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function
std::vector<student>* mergeSortThread(int begin, int end, std::vector<student>* studs)
{
	std::vector<student> b = std::vector<student>();
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
	struct thread_args *threadArgs = (struct thread_args *)param;
	int begin = threadArgs->threadNum * threadArgs->sizeofVector;
	int end = (threadArgs->threadNum+1) * threadArgs->sizeofVector;
	//std::cout << "STARTED MERGE " << std::endl;
	//std::cout <<"begin is " << begin << "end is " << end << std::endl;
	//std::cout <<"vector size is " << threadArgs->sV->size()<<std::endl;
	std::cout <<"thread num is " <<threadArgs->threadNum << std::endl;
	std::vector<student> temp;
	for(int i = begin; i < end; i++)
	{
		temp.push_back(threadArgs->sV->at(i));
	}
	//std::vector<student>temp(first,last);
	//threadArgs->sortedThreads->push_back(std::vector<student>());
	mergeSortThread(begin, end, &temp);
	printf("threading this\n");
	threadArgs->sortedThreads->push_back(temp);
	return NULL;
}	//creates thread

void split(std::vector<student> *D, int iBegin, int iEnd, std::vector<student> *C)
{
	if(iEnd - iBegin < 2)
		return;
	int iMiddle = (iBegin + iEnd)/2;
	split(C, iBegin, iMiddle, D);
	split(C, iMiddle, iEnd, D);
	Merge(D, iBegin, iMiddle, iEnd, C);
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


void Merge2(std::vector<student> *A,  std::vector<student> *B)
{
	std::vector<student> *result = new std::vector<student>();
	while (!A->empty() | !B->empty())
	{
		if(A->front().getScore() > B->front().getScore())
		{
			result->push_back(A->front());
			A->erase(A->begin());
		}
		else
		{
			result->push_back(B->front());
			B->erase(B->begin());
		}
	}

	while(!A->empty())
	{
		result->push_back(A->front());
		A->erase(A->begin());
	}
	while(!B->empty())
	{
		result->push_back(B->front());
		B->erase(B->begin());
	}
	A = result;
	return;
}
