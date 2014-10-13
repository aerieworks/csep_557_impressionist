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
  PointBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL) : ImpBrush(pDoc, name) {}

  virtual BrushStroke* createStroke();
protected:
  class PointBrushStroke : public ImpBrush::BrushStroke {
  public:
    PointBrushStroke(ImpressionistDoc* const doc, const BrushSettings* settings) : BrushStroke(doc, settings) {}
      
    virtual void begin();
  protected:
    virtual void doPaint(const BrushSettings* settings, const Point source, const Point target);
  };
};

#endif
