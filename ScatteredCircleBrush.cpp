#include <iostream>
#include <random>
#include <time.h>
#include "impressionistDoc.h"
#include "ScatteredCircleBrush.h"

#define OFFSET_MIN -10
#define OFFSET_MAX 10

using namespace std;

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc * pDoc, char * name) :
	CircleBrush(pDoc, name)
{
	srand(time(0));
}

double ScatteredCircleBrush::getRandomOffset()
{
	return OFFSET_MIN + (OFFSET_MAX - OFFSET_MIN) * ((double)rand()) / ((double)RAND_MAX);
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	Point * scatteredTarget = new Point(target.x + getRandomOffset(), target.y + getRandomOffset());
	CircleBrush::BrushMove(source, *scatteredTarget);
	delete scatteredTarget;
}
