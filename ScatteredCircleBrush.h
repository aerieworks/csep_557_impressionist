#include "Scattered.h"

#pragma once
#include "CircleBrush.h"
class ScatteredCircleBrush :
	public CircleBrush, Scattered
{
public:
	ScatteredCircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

	void BrushMove(const Point source, const Point target);
};

