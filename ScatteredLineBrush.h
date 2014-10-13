#pragma once
#include "LineBrush.h"
class ScatteredLineBrush : public LineBrush {
public:
  ScatteredLineBrush(ImpressionistDoc * pDoc = NULL, char * name = NULL) : LineBrush(pDoc, name) {}

  virtual BrushStroke* createStroke();
protected:
  class ScatteredLineBrushStroke : public LineBrush::LineBrushStroke {
  public:
    ScatteredLineBrushStroke(ImpressionistDoc* const doc, const BrushSettings* settings)
      : LineBrushStroke(doc, settings) {}

    virtual void resolveSettings(BrushSettings* settings, const Point source) const;
    virtual void paint(const Point source, const Point target);
  };
};

