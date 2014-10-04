#include "impBrush.h"

#pragma once
class Scattered
{
public:
	Scattered();

protected:
	Point GetScatteredTarget(const Point originalTarget) const;

private:
	int AddRandomOffset(const int initialValue) const;
};

