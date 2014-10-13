#include "ScatteredPointBrush.h"

void ScatteredPointBrush::ScatteredPointBrushStroke::paint(const Point source, const Point target) {
  Point scatteredTarget = Scattered::getScatteredTarget(target);
  PointBrushStroke::paint(source, scatteredTarget);
}

ImpBrush::BrushStroke* ScatteredPointBrush::createStroke() {
  return new ScatteredPointBrush::ScatteredPointBrushStroke(getDocument(), getSettings());
}
