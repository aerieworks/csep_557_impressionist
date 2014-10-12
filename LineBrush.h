#pragma once
#include "impBrush.h"
class LineBrush :
	public ImpBrush
{
public:
	LineBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

	Area* BrushBegin(const Point source, const Point target);
	Area* BrushMove(const Point source, const Point target);
	Area* BrushEnd(const Point source, const Point target);
	char * BrushName(void);
};

