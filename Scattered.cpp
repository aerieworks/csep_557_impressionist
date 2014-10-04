#include <random>
#include <time.h>
#include "Scattered.h"


#define OFFSET_MIN -10
#define OFFSET_MAX 10

Scattered::Scattered()
{
	srand(time(0));
}

double Scattered::getRandomOffset()
{
	return OFFSET_MIN + (OFFSET_MAX - OFFSET_MIN) * ((double)rand()) / ((double)RAND_MAX);
}

Point Scattered::getScatteredTarget(const Point originalTarget)
{
	return Point(originalTarget.x + getRandomOffset(), originalTarget.y + getRandomOffset());
}