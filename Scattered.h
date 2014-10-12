#include "impBrush.h"

#pragma once
class Scattered {
public:
  Scattered();

protected:
  Point getScatteredTarget(const Point originalTarget) const;

private:
  int addRandomOffset(const int initialValue) const;
};

