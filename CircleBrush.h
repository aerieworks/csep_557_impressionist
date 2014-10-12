#pragma once
#include "impBrush.h"
class CircleBrush :
  public ImpBrush {
public:
  CircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

  Area* brushBegin(const Point source, const Point target);
  virtual Area* brushMove(const Point source, const Point target);
  Area* brushEnd(const Point source, const Point target);
  Area* getModifiedArea(const Point target);
  char * getBrushName(void);
};

