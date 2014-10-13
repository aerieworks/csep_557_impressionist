#pragma once
#include "pointBrush.h"

class ScatteredPointBrush : public PointBrush {
public:
  ScatteredPointBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL) : PointBrush(pDoc, name) {}

  virtual BrushStroke* createStroke();
protected:
  class ScatteredPointBrushStroke : public PointBrush::PointBrushStroke {
  public:
    ScatteredPointBrushStroke(ImpressionistDoc* const doc, const BrushSettings* settings)
      : PointBrushStroke(doc, settings) {}

    virtual void resolveSettings(BrushSettings* settings, const Point source) const;
    virtual void paint(const Point source, const Point target);
  };
};

