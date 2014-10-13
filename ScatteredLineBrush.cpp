#include "ScatteredLineBrush.h"

void ScatteredLineBrush::ScatteredLineBrushStroke::paint(const Point source, const Point target) {
  Point scatteredTarget = Scattered::getScatteredTarget(target);
  LineBrushStroke::paint(source, scatteredTarget);
}

ImpBrush::BrushStroke* ScatteredLineBrush::createStroke() {
  return new ScatteredLineBrush::ScatteredLineBrushStroke(getDocument(), getSettings());
}
