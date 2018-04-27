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
	//std::cout <<"begin was " << begin << "end is " << end << std::endl;
	return studs;
}

void *runnable(void *param)
{
	assert(param);
	struct thread_args *threadArgs = (struct thread_args *)param;
	mergeSortThread(threadArgs->begin, threadArgs->end, threadArgs->sV);

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


void Merge2(std::vector<student> *C, int begin, int middle, int end, std::vector<student> *D)
{
	assert(C);
	assert(D);
	int i = begin;
	int j = middle;
	for(int k = begin; k < end; k++)
	{
		if(i < middle && (j>=end || C->at(i).getScore() <= C->at(j).getScore()))
		{
			D->push_back(C->at(i));
			i++;
		}
		else
		{
			D->push_back(C->at(j));
			j++;
		}
	}
}

