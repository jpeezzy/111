#include "student.h"

student::student(long _id, double _score)
{
	id = _id;
	score = _score;
}

long student::getId()
{
	return id;
}

double student::getScore()
{
	return score;
}
