#include "ScatteredPointBrush.h"

void ScatteredPointBrush::ScatteredPointBrushStroke::paint(const Point source, const Point target) {
  const double size = settings->getSizeAsDouble();
  for (int i = 0; i < 10; i++) {
    const int xOffset = (int)Scattered::getRandomOffset(-size, size);
    const int yOffset = (int)Scattered::getRandomOffset(-size, size);
    PointBrushStroke::paint(Point(source.x + xOffset, source.y + yOffset), Point(target.x + xOffset, target.y + yOffset));
  }
}

void ScatteredPointBrush::ScatteredPointBrushStroke::resolveSettings(BrushSettings* settings, const Point source) const {
  settings->setSize((int)(settings->getSizeAsDouble() / 4));
  PointBrushStroke::resolveSettings(settings, source);
}

ImpBrush::BrushStroke* ScatteredPointBrush::createStroke() {
  return new ScatteredPointBrush::ScatteredPointBrushStroke(getDocument(), getSettings());
}
