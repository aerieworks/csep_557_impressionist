#include "BrushBeginAction.h"


BrushBeginAction::BrushBeginAction(ImpBrush* brush, const Point source, const Point target)
  : BrushAction(brush, source, target) {
}

Area* BrushBeginAction::doAction() {
  return brush->brushBegin(source, target);
}