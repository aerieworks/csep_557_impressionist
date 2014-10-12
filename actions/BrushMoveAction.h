#pragma once
#include "BrushAction.h"
class BrushMoveAction :
  public BrushAction {
public:
  BrushMoveAction(ImpBrush* brush, const Point source, const Point target);
  Area* doAction();
};

