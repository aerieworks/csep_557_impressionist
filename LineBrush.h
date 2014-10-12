#pragma once
#include "impBrush.h"
#include "KernelFilter.h"

class LineBrush :
  public ImpBrush {
public:
  LineBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL);
  ~LineBrush();

  Area* brushBegin(const Point source, const Point target);
  Area* brushMove(const Point source, const Point target);
  Area* brushEnd(const Point source, const Point target);
  char * getBrushName(void);

private:
  double calculateDirection(const Point source);
  KernelFilter* sobelOperatorX;
  KernelFilter* sobelOperatorY;
};

