#include "impBrush.h"

#pragma once
class Scattered
{
public:
	Scattered();

protected:
	Point getScatteredTarget(const Point originalTarget);

private:
	double getRandomOffset();
};

