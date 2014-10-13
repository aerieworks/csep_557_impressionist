#pragma once
#include "BrushAction.h"
class BrushBeginAction :
  public BrushAction {
public:
  BrushBeginAction(ImpBrush::BrushStroke* stroke, const Point source, const Point target) : BrushAction(stroke, source, target) {}
  bool doAction();
};

