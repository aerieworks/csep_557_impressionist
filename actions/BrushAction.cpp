#include "BrushAction.h"


BrushAction::BrushAction(ImpBrush::BrushStroke* stroke, const Point source, const Point target)
  : stroke(stroke), source(source), target(target) {
}
