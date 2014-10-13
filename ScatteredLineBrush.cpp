#include "ScatteredLineBrush.h"

void ScatteredLineBrush::ScatteredLineBrushStroke::paint(const Point source, const Point target) {
  const double size = settings->getSizeAsDouble();
  for (int i = 0; i < 10; i++) {
    const int xOffset = (int)Scattered::getRandomOffset(-size, size);
    const int yOffset = (int)Scattered::getRandomOffset(-size, size);
    LineBrushStroke::paint(Point(source.x + xOffset, source.y + yOffset), Point(target.x + xOffset, target.y + yOffset));
  }
}

void ScatteredLineBrush::ScatteredLineBrushStroke::resolveSettings(BrushSettings* settings, const Point source) const {
  settings->setSize((int)(settings->getSizeAsDouble() / 4));
  LineBrushStroke::resolveSettings(settings, source);
}

ImpBrush::BrushStroke* ScatteredLineBrush::createStroke() {
  return new ScatteredLineBrush::ScatteredLineBrushStroke(getDocument(), getSettings());
}
