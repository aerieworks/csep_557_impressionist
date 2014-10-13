#pragma once
#include "pointBrush.h"
#include "Scattered.h"

class ScatteredPointBrush : public PointBrush {
public:
  ScatteredPointBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL) : PointBrush(pDoc, name) {}

  virtual BrushStroke* createStroke();
protected:
  class ScatteredPointBrushStroke : public PointBrush::PointBrushStroke, Scattered {
  public:
    ScatteredPointBrushStroke(ImpressionistDoc* const doc, const BrushSettings* settings)
      : PointBrushStroke(doc, settings), Scattered() {}

    virtual void resolveSettings(BrushSettings* settings, const Point source) const;
    virtual void paint(const Point source, const Point target);
  };
};

