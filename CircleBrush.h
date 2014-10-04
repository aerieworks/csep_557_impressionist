#pragma once
#include "impBrush.h"
class CircleBrush :
	public ImpBrush
{
public:
	CircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

	void BrushBegin(const Point source, const Point target);
	virtual void BrushMove(const Point source, const Point target);
	void BrushEnd(const Point source, const Point target);
	char * BrushName(void);
};

