#pragma once
#include "BrushAction.h"
class BrushMoveAction : public BrushAction {
public:
  BrushMoveAction(ImpBrush::BrushStroke* stroke, const Point source, const Point target) : BrushAction(stroke, source, target) {}
  bool doAction();
};

