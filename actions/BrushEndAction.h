#pragma once
#include "BrushAction.h"
class BrushEndAction :
	public BrushAction
{
public:
	BrushEndAction(ImpBrush* brush, const Point source, const Point target);
	Area* DoAction();
};

