#pragma once
#include "impBrush.h"
class CircleBrush : public ImpBrush {
public:
  CircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL) : ImpBrush(pDoc, name) {}

  virtual BrushStroke* createStroke();
protected:
  class CircleBrushStroke : public ImpBrush::BrushStroke {
  public:
    CircleBrushStroke(ImpressionistDoc* const doc, const BrushSettings* settings) : BrushStroke(doc, settings) {}
      
    virtual void begin();
  protected:
    virtual void doPaint(const BrushSettings* settings, const Point source, const Point target);
  };
};

