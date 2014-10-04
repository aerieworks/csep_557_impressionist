#include <random>
#include <time.h>
#include "Scattered.h"


#define OFFSET_MIN -10
#define OFFSET_MAX 10

Scattered::Scattered()
{
	srand(time(0));
}

int Scattered::AddRandomOffset(const int initialValue) const
{
	const double offsetPercentage = (double)rand() / (double)RAND_MAX;
	const int offsetValue = (int)floor((OFFSET_MAX - OFFSET_MIN) * offsetPercentage);
	return initialValue + OFFSET_MIN + offsetValue;
}

Point Scattered::GetScatteredTarget(const Point originalTarget) const
{
	return Point(AddRandomOffset(originalTarget.x), AddRandomOffset(originalTarget.y));
}