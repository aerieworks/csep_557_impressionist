#pragma once
#include "pointBrush.h"
#include "Scattered.h"

class ScatteredPointBrush :
	public PointBrush, Scattered
{
public:
	ScatteredPointBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);
	Area* BrushMove(const Point source, const Point target);
};

