#pragma once
#include "impBrush.h"
#include "KernelFilter.h"

class LineBrush : public ImpBrush {
public:
  LineBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL) : ImpBrush(pDoc, name) {}

  virtual BrushStroke* createStroke();
protected:
  const static double sobelXMatrix[9];
  const static double sobelYMatrix[9];
  const static KernelFilter sobelOperatorX;
  const static KernelFilter sobelOperatorY;

  class LineBrushStroke : public ImpBrush::BrushStroke {
  public:
    LineBrushStroke(ImpressionistDoc* const doc, const BrushSettings* settings) : BrushStroke(doc, settings) {}
      
    virtual void begin();
  protected:
    double calculateDirection(const Point source) const;
    virtual void resolveSettings(BrushSettings* settings, const Point source) const;
    virtual void doPaint(const BrushSettings* settings, const Point source, const Point target);
  };
};

