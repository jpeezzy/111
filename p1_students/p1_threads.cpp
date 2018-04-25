#include "p1_threads.h"
#include <assert.h>
// This file includes functions that actually perform the
// computation. You can create a thread with these function
// or directly call this function
std::vector<student>* mergeSortThread(int begin, int end, std::vector<student>* studs)
{
	assert(studs);
	std::vector<student> b;
	b.reserve(1000000);
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
	assert(param);
	struct thread_args *threadArgs = (struct thread_args *)param;
	int begin = threadArgs->threadNum * threadArgs->sizeofVector;
	int end = (threadArgs->threadNum+1) * threadArgs->sizeofVector;
	//std::cout << "STARTED MERGE " << std::endl;
	//std::cout <<"begin is " << begin << "end is " << end << std::endl;
	//std::cout <<"vector size is " << threadArgs->sV->size()<<std::endl;
//	std::cout <<"thread num is " <<threadArgs->threadNum << std::endl;
	std::vector<student> temp;
	temp.reserve(1000000);
	for(int i = begin; i < end; i++)
	{
		temp.push_back(threadArgs->sV->at(i));
	}
	//std::vector<student>temp(first,last);
	mergeSortThread(0, end-begin, &temp);
//	printf("threading this\n");
	int thread_end = threadArgs->sortedThreads->size()-1;
	if(thread_end < 0)
	{
		threadArgs->sortedThreads->push_back(temp);
		thread_end=0;
	}
	else
	{
		threadArgs->sortedThreads->push_back(temp);
	}
	thread_end = threadArgs->sortedThreads->size()-1;
	std::cout <<"the returned thing is " << threadArgs->sortedThreads->at(thread_end).size()<<std::endl;

	return NULL;
}	//creates thread

void split(std::vector<student> *D, int iBegin, int iEnd, std::vector<student> *C)
{
	assert(C);
	if(iEnd - iBegin < 2)
		return;
	int iMiddle = (iBegin + iEnd)/2;
	split(C, iBegin, iMiddle, D);
	split(C, iMiddle, iEnd, D);
	Merge(D, iBegin, iMiddle, iEnd, C);
}

void Merge(std::vector<student> *C, int begin, int middle, int end, std::vector<student> *D)
{
	assert(C);
	assert(D);
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


void Merge2(std::vector<student> *A,  std::vector<student> *B, std::vector<student>* result)
{

	unsigned int A_count = 0;
	unsigned int B_count = 0;
	std::vector<student>::iterator itA = A->begin();
	std::vector<student>::iterator itB = B->begin();
	/*
	if(A->size() != B->size())
	{
		return;
	}*/
	//result->clear();
	if(A->empty() || B->empty())
	{
		std::cout << "A or b is empty" <<std::endl;
		return;
	}
	std::cout << "sizeof A is " << A->size() << std::endl;;
	std::cout << "sizeof B is " << B->size() << std::endl;;

	while(true)
	{
		if(A->at(A_count).getScore() >= B->at(B_count).getScore())
		{
			result->push_back(A->at(A_count));
			A_count++;
		}
		else
		{
			result->push_back(B->at(B_count));
			B_count++;
		}
		if(A_count >= (A->size()-1) || (B_count >= B->size()-1))
		{
			break;
		}
	}
	//std::cout <<" FINISHED first part for merge " << std::endl;
	while(A_count < A->size())
	{
		result->push_back(A->at(A_count));
		A_count++;
	}
	//std::cout <<" FINISHED second part for merge " << std::endl;
	while(B_count < B->size())
	{
		result->push_back(B->at(B_count));
		B_count++;
	}
	//std::cout <<" FINISHED third part for merge " << std::endl;
	return;
}
