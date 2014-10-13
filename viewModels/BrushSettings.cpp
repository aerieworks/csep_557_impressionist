#include <string>
#include "BrushSettings.h"
#include "../Log.h"

#define DEFAULT_LINE_WIDTH 1
#define DEFAULT_OPACITY 255
#define DEFAULT_SIZE 20
#define DEFAULT_BRUSH_DIRECTION 0

BrushSettings::BrushSettings()
  : colorMode(ColorMode::FromSource),
    lineWidth(DEFAULT_LINE_WIDTH),
    opacity(DEFAULT_OPACITY),
    size(DEFAULT_SIZE),
    brushDirection(DEFAULT_BRUSH_DIRECTION),
    directionMode(DirectionMode::FixedDirection) {
  color[0] = 0;
  color[1] = 0;
  color[2] = 0;
  color[3] = 255;
}

BrushSettings::BrushSettings(const BrushSettings& settings)
  : colorMode(settings.colorMode),
    lineWidth(settings.lineWidth),
    opacity(settings.opacity),
    size(settings.size),
    brushDirection(settings.brushDirection),
    directionMode(settings.directionMode) {
  setColor(settings.color);
  Log::Debug << "Copied settings." << Log::end;
  Log::printSettings(this);
}

ColorMode BrushSettings::getColorMode() const {
  return colorMode;
}

void BrushSettings::setColorMode(ColorMode mode) {
  this->colorMode = mode;
}

const unsigned char* BrushSettings::getColor() const {
  return color;
}

void BrushSettings::setColor(const unsigned char* color) {
  memcpy(this->color, color, 4);
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
