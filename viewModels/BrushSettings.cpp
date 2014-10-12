#include "BrushSettings.h"

#define DEFAULT_LINE_WIDTH 1
#define DEFAULT_OPACITY 255
#define DEFAULT_SIZE 20
#define DEFAULT_BRUSH_DIRECTION 0

BrushSettings::BrushSettings()
  : lineWidth(DEFAULT_LINE_WIDTH),
  opacity(DEFAULT_OPACITY),
  size(DEFAULT_SIZE),
  brushDirection(DEFAULT_BRUSH_DIRECTION),
  directionMode(DirectionMode::Fixed) {
}

double BrushSettings::getLineWidthAsDouble() const {
  return lineWidth;
}

float BrushSettings::getLineWidthAsFloat() const {
  return (float)lineWidth;
}

void BrushSettings::setLineWidth(const double lineWidth) {
  this->lineWidth = lineWidth;
}

char BrushSettings::getOpacityAsChar() const {
  return (char)opacity;
}

double BrushSettings::getOpacityAsDouble() const {
  return opacity;
}

void BrushSettings::setOpacity(const double opacity) {
  this->opacity = opacity;
}

int BrushSettings::getSizeAsInteger() const {
  return size;
}

double BrushSettings::getSizeAsDouble() const {
  return (double)size;
}

float BrushSettings::getSizeAsFloat() const {
  return (float)size;
}

void BrushSettings::setSize(const int size) {
  this->size = size;
}

double BrushSettings::getBrushDirectionAsDouble() const {
  return brushDirection;
}

void BrushSettings::setBrushDirection(const double brushDirection) {
  this->brushDirection = brushDirection;
}

DirectionMode BrushSettings::getBrushDirectionMode() const {
  return directionMode;
}

void BrushSettings::setBrushDirectionMode(const DirectionMode directionMode) {
  this->directionMode = directionMode;
}
