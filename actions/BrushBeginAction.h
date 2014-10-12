#pragma once
#include "BrushAction.h"
class BrushBeginAction :
  public BrushAction {
public:
  BrushBeginAction(ImpBrush* brush, const Point source, const Point target);
  Area* doAction();
};

