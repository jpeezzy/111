#include "student.h"
#include "p1_process.h"
#include <iomanip>      // std::setprecision
#include <sstream> //string stream

void get_statistics(std::string class_name[], int num_processes, int num_threads, int num_files) 
{
	printf("creating a maximum of %d processes\n", num_processes);
	int filesLeft = num_files - 1;

	for(int i = 0; i < num_processes; i++)
	{
		if(fork() == 0)
		{
			bool endChild = 0;
			//printf("Hello from child!\n");
			while(endChild == 0)
			{
				int filenumber = filesLeft;
				//printf("creating a maximum of %d threads\n", num_threads);
				//creating a vector of PIDs
				//accessing the file based off class name;
				//stores the students in a vector
				std::vector<student> students = getStudents(class_name[filenumber]);
				std::cout.precision(12);
				int sizeofVector = students.size()/num_threads;

				//parameters in the runnable thread function 
				//holds the number of threads, the index, how big vector is, 
				//and how much is left from dividing evenly
				pthread_t tid[num_threads];
				pthread_attr_t attr[num_threads];
				struct thread_args targs;
				targs.num_threads = num_threads;
				targs.threadNum = 0;
				targs.sizeofVector = sizeofVector;
				targs.sV = &students;
				//split up the vector based off how many threads we have

				for(int j = 0; j < num_threads; j++)
				{
					pthread_attr_init(&attr[j]);
					targs.threadNum = j;
					pthread_create(&tid[j],&attr[j], runnable, (void*)&targs);
				}
				for(int k = 0; k < num_threads; k++)
				{
					pthread_join(tid[k], NULL);
					printf("Thread %lu deleted \n", tid[k]);
				}
				writeToFile(students, class_name[filenumber]);
				filesLeft--;
				//write the "sorted vector" to file
				if(filesLeft < 0)
				{
					break;
					endChild=1;
				}
			}
			exit(EXIT_SUCCESS);
		}
		else
		{
			printf("Hello from parent !\n");
		}
	}
	//wait for all child processes
	while((wait(0))>0) {}
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
		ofFile << i << "," << it->getId() << "," << it->getScore() << "\n";
	}
	return;
}
