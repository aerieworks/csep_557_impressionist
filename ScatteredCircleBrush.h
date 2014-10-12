#pragma once
#include "CircleBrush.h"
#include "Scattered.h"
class ScatteredCircleBrush :
	public CircleBrush, Scattered
{
public:
	ScatteredCircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

	Area* BrushMove(const Point source, const Point target);
};

