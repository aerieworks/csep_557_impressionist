#pragma once
#include "impBrush.h"
class CircleBrush :
	public ImpBrush
{
public:
	CircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

	Area* BrushBegin(const Point source, const Point target);
	virtual Area* BrushMove(const Point source, const Point target);
	Area* BrushEnd(const Point source, const Point target);
	Area* GetModifiedArea(const Point target);
	char * BrushName(void);
};

