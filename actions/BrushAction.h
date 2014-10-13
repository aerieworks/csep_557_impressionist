#pragma once
#include "Action.h"
#include "../ImpBrush.h"
class BrushAction : public Action {
public:
  BrushAction(ImpBrush::BrushStroke* stroke, const Point source, const Point target) : stroke(stroke), source(source), target(target) {}
protected:
  ImpBrush::BrushStroke* stroke;
  const Point source;
  const Point target;
};

