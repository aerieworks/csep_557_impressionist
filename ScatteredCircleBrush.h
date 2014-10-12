#pragma once
#include "CircleBrush.h"
#include "Scattered.h"
class ScatteredCircleBrush :
  public CircleBrush, Scattered {
public:
  ScatteredCircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

  Area* brushMove(const Point source, const Point target);
};

