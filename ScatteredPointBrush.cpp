#include "ScatteredPointBrush.h"

void ScatteredPointBrush::ScatteredPointBrushStroke::paint(const Point source, const Point target) {
  const double size = settings->getSizeAsDouble();
  const int count = (int)getRandomOffset(settings->getScatterMinCountAsInteger(), settings->getScatterMaxCountAsInteger());
  for (int i = 0; i < count; i++) {
    const int xOffset = (int)getRandomOffset(-size, size);
    const int yOffset = (int)getRandomOffset(-size, size);
    PointBrushStroke::paint(Point(source.x + xOffset, source.y + yOffset), Point(target.x + xOffset, target.y + yOffset));
  }
}

void ScatteredPointBrush::ScatteredPointBrushStroke::resolveSettings(BrushSettings* settings, const Point source) const {
  settings->setSize((int)getRandomOffset(settings->getScatterMinSizeAsDouble(), settings->getScatterMaxSizeAsDouble()));
  PointBrushStroke::resolveSettings(settings, source);
}

ImpBrush::BrushStroke* ScatteredPointBrush::createStroke() {
  return new ScatteredPointBrush::ScatteredPointBrushStroke(getDocument(), getSettings());
}
