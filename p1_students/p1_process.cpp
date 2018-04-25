#include "student.h"
#include "p1_process.h"
#include <iomanip>      // std::setprecision
#include <sstream> //string stream
#include <math.h>
#include <sys/mman.h>

static int *filesLeft;
void get_statistics(std::string class_name[], int num_processes, int num_threads, int num_files) 
{
	filesLeft = (int*)mmap(NULL, sizeof *filesLeft, PROT_READ | PROT_WRITE, 
			MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	printf("creating a maximum of %d processes\n", num_processes);
	*filesLeft = num_files;

	for(int i = 0; i < num_processes; i++)
	{
		if(fork())
		{
			bool endChild = 0;
			//printf("Hello from child!\n");
			while(endChild == 0)
			{
				//std::cout << "File num is " <<std::endl;
				int filenumber = --*filesLeft;
				if(*filesLeft < 0)
				{
					break;
					endChild=1;
				}
				//printf("creating a maximum of %d threads\n", num_threads);

				std::vector<student> students = getStudents(class_name[filenumber]);

				int sizeofVector = students.size()/num_threads;
				std::vector<std::vector<student> > studVects;
				studVects.reserve(100);
				pthread_t tid[num_threads];
				pthread_attr_t attr[num_threads];
				//split up the vector based off how many threads we have

				for(int j = 0; j < num_threads; j++)
				{
					struct thread_args targs;
					targs.num_threads = num_threads;
					targs.sizeofVector = sizeofVector;
					targs.sortedThreads = &studVects;
					targs.sV = &students;
					targs.threadNum = j;
					pthread_attr_init(&attr[j]);
					pthread_create(&tid[j],&attr[j], runnable, (void*)&targs);
				}

				for(int k = 0; k < num_threads; k++)
				{
					pthread_join(tid[k], NULL);
					//printf("Thread %lu deleted \n", tid[k]);
				}

				std::cout <<"all threads joined!" <<std::endl;
				//Merge the threads 
				std::vector<student> final_result;
				final_result.reserve(1000000);
				if(num_threads > 1)
				{
					//std::cout<<"the size of studVects is " << studVects.size()<<std::endl;
					Merge2(&studVects[0], &studVects[1], &final_result);
					std::cout<<"finished merging all threads !"<<std::endl;
					//std::cout <<"starting to merge all threads" << std::endl;
					/*for(int x = 2; x <num_threads;x++)
					  {
					//std::cout<<"finished merging all threads !"<<std::endl;
					//std::vector<student> temp = final_result; 
					//Merge2(&temp, &studVects.at(x), final_result);
					}*/
					//std::cout<<"finished merging all threads !"<<std::endl;
					//final_result = studVects.at(0);
				}
				else
				{
					final_result = studVects.at(0);
				}
					writeToFile(final_result, class_name[filenumber]);
					double m = mean(final_result);
					double stdDev = standardDeiviation(final_result);
					double med = median(final_result);
					writeStatistics(final_result, class_name[filenumber], m, med, stdDev);
					std::cout<<"finished merging all threads !"<<std::endl;
				//write the "sorted vector" to file
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			//printf("Creating child thread %d \n", *filesLeft);
		}
	}
	//wait for all child processes
	while((wait(0))>0) {}
	munmap(filesLeft, sizeof *filesLeft);
	return;
}

std::vector<student> getStudents(std::string class_name)
{
	std::string tempVar = "input/" + class_name + ".csv";
	std::ifstream inFile;
	std::vector<student> studentScores;


	inFile.open(tempVar.c_str());
	if(!inFile)
	{
		perror("Cannot find file!");
		exit(0);
	}

	//skip fthe first line
	std::string tempScoreLine;
	std::getline(inFile, tempScoreLine);
	while(std::getline(inFile, tempScoreLine))
	{
		std::string::size_type comma = tempScoreLine.find(",");
		std::string tStudent = tempScoreLine.substr(0, comma-1);
		std::string tScore = tempScoreLine.substr(comma+1, tempScoreLine.size());
		//std::cout <<"tstudent here is " << tStudent << std::endl;
		std::setprecision(12);
		std::stringstream ss(tStudent);
		long ID;
		ss >> ID;
		std::stringstream sScore(tScore);
		double Score;
		sScore >> std::setprecision(12) >> Score;
		studentScores.push_back (student(ID, Score));
		//std::cout <<tScore << std::endl;
	}
	inFile.close();
	return studentScores;
}

void writeToFile(std::vector<student> stud, std::string class_name)
{
	std::ofstream ofFile;
	std::string dir = "output/" + class_name + "_sorted.csv";

	ofFile.open(dir.c_str(), std::ofstream::out | std::ofstream::trunc);

	ofFile << "Rank,id,score" << std::endl;
	int i;
	std::vector<student>::reverse_iterator it;
	for(i = 1, it = stud.rbegin(); it != stud.rend(); i++, it++)
	{
		ofFile << i << "," << it->getId() << "," << std::setprecision(12) << it->getScore() << "\n";
	}
	ofFile.close();
	return;
}


double mean(std::vector<student> students)
{
	std::vector<student>::iterator it;
	double score;
	for(it = students.begin(); it != students.end(); it++)
	{
		score += it->getScore();	
	}
	return score/students.size();
}

double standardDeiviation(std::vector<student> students)
{
	double m = mean(students);
	std::vector<student>::iterator it;
	double score = 0;
	for(it = students.begin(); it != students.end(); it++)
	{
		score += pow(it->getScore() - m ,2);
	}

	return pow(score/students.size(), 0.5);
}

double median(std::vector<student> students)
{
	return students.at(students.size()/2).getScore();
}

void writeStatistics(std::vector<student> stud, std::string class_name, double mean, double median, double standardDeviation)
{
	std::ofstream ofFile;
	std::string dir = "output/" + class_name + "_statistics.csv";

	ofFile.open(dir.c_str(), std::ofstream::out | std::ofstream::trunc);

	ofFile << "mean,median,standardDeiviation" << std::endl;
	ofFile << mean << "," << median << "," << standardDeiviation << std::endl;
	ofFile.close();
	return;
}
