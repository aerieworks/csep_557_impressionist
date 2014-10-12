#include "BrushMoveAction.h"


BrushMoveAction::BrushMoveAction(ImpBrush* brush, const Point source, const Point target)
  : BrushAction(brush, source, target) {
}

Area* BrushMoveAction::doAction() {
  return brush->brushMove(source, target);
}