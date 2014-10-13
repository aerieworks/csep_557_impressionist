#pragma once
#include "BrushAction.h"
#include "../impressionistDoc.h"

class BrushEndAction : public BrushAction {
public:
  BrushEndAction(ImpressionistDoc* doc, ImpBrush::BrushStroke* stroke, const Point source, const Point target)
    : BrushAction(stroke, source, target), doc(doc) {}

  bool doAction();
private:
  ImpressionistDoc* doc;
};

