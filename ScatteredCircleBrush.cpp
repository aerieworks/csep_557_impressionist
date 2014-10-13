#include "impressionistDoc.h"
#include "ScatteredCircleBrush.h"

void ScatteredCircleBrush::ScatteredCircleBrushStroke::paint(const Point source, const Point target) {
  Point scatteredTarget = Scattered::getScatteredTarget(target);
  CircleBrushStroke::paint(source, scatteredTarget);
}

ImpBrush::BrushStroke* ScatteredCircleBrush::createStroke() {
  return new ScatteredCircleBrush::ScatteredCircleBrushStroke(getDocument(), getSettings());
}
