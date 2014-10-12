#pragma once
#include "Action.h"
#include "../ImpBrush.h"
class BrushAction :
  public Action {
public:
  BrushAction(ImpBrush* brush, const Point source, const Point target);
protected:
  ImpBrush* brush;
  const Point source;
  const Point target;
};

