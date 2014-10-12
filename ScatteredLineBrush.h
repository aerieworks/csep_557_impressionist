#pragma once
#include "LineBrush.h"
#include "Scattered.h"
class ScatteredLineBrush :
	public LineBrush, Scattered
{
public:
	ScatteredLineBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

	Area* BrushMove(const Point source, const Point target);
};

