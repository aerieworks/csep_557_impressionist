#pragma once
#include "impBrush.h"
class LineBrush :
  public ImpBrush {
public:
  LineBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);

  Area* brushBegin(const Point source, const Point target);
  Area* brushMove(const Point source, const Point target);
  Area* brushEnd(const Point source, const Point target);
  char * getBrushName(void);
};

