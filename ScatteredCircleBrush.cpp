#include "impressionistDoc.h"
#include "ScatteredCircleBrush.h"

void ScatteredCircleBrush::ScatteredCircleBrushStroke::paint(const Point source, const Point target) {
  const double size = settings->getSizeAsDouble();
  for (int i = 0; i < 10; i++) {
    const double angle = Scattered::getRandomOffset(0, 2 * PI);
    const double radius = Scattered::getRandomOffset(0, size);
    const int xOffset = radius * cos(angle);
    const int yOffset = radius * sin(angle);
    CircleBrushStroke::paint(Point(source.x + xOffset, source.y + yOffset), Point(target.x + xOffset, target.y + yOffset));
  }
}

void ScatteredCircleBrush::ScatteredCircleBrushStroke::resolveSettings(BrushSettings* settings, const Point source) const {
  settings->setSize((int)(settings->getSizeAsDouble() / 4));
  CircleBrushStroke::resolveSettings(settings, source);
}

ImpBrush::BrushStroke* ScatteredCircleBrush::createStroke() {
  return new ScatteredCircleBrush::ScatteredCircleBrushStroke(getDocument(), getSettings());
}
