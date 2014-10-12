//
// pointBrush.h
//
// The header file for Point Brush. 
//

#ifndef POINTBRUSH_H
#define POINTBRUSH_H

#include "impBrush.h"

class PointBrush : public ImpBrush {
public:
  PointBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

  Area* brushBegin(const Point source, const Point target);
  Area* brushMove(const Point source, const Point target);
  Area* brushEnd(const Point source, const Point target);
  char* getBrushName(void);
private:
  Area* getModifiedArea(const Point target);
};

#endif
