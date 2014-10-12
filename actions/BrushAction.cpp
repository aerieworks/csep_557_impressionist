#include "BrushAction.h"


BrushAction::BrushAction(ImpBrush* brush, const Point source, const Point target)
  : brush(brush), source(source), target(target) {
}
