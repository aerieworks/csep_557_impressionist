#pragma once
#include "CircleBrush.h"
class ScatteredCircleBrush : public CircleBrush {
public:
  ScatteredCircleBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL) : CircleBrush(pDoc, name) {}

  virtual BrushStroke* createStroke();
protected:
  class ScatteredCircleBrushStroke : public CircleBrush::CircleBrushStroke {
  public:
    ScatteredCircleBrushStroke(ImpressionistDoc* const doc, const BrushSettings* settings)
      : CircleBrushStroke(doc, settings) {}

    virtual void resolveSettings(BrushSettings* settings, const Point source) const;
    virtual void paint(const Point source, const Point target);
  };
};

