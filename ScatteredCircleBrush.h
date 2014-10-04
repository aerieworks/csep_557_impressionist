#pragma once
#include "CircleBrush.h"
class ScatteredCircleBrush :
	public CircleBrush
{
public:
	ScatteredCircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

	void BrushMove(const Point source, const Point target);

private:
	double getRandomOffset();
};

