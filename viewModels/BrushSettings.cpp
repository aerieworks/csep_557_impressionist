#include <string>
#include "BrushSettings.h"

BrushSettings::BrushSettings()
  : colorMode(ColorMode::FromSource),
    lineWidth(1),
    opacity(255),
    size(20),
    brushDirection(0),
    directionMode(DirectionMode::FixedDirection),
    scatterMinSize(1),
    scatterMaxSize(5),
    scatterMinCount(3),
    scatterMaxCount(8) {
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
    directionMode(settings.directionMode),
    scatterMinSize(settings.scatterMinSize),
    scatterMaxSize(settings.scatterMaxSize),
    scatterMinCount(settings.scatterMinCount),
    scatterMaxCount(settings.scatterMaxCount) {
  setColor(settings.color);
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

double BrushSettings::getScatterMinSizeAsDouble() const {
  return scatterMinSize;
}

void BrushSettings::setScatterMinSize(const double size) {
  this->scatterMinSize = size;
}

double BrushSettings::getScatterMaxSizeAsDouble() const {
  return scatterMaxSize;
}

void BrushSettings::setScatterMaxSize(const double size) {
  this->scatterMaxSize = size;
}

int BrushSettings::getScatterMinCountAsInteger() const {
  return scatterMinCount;
}
void BrushSettings::setScatterMinCount(const int count) {
  this->scatterMinCount = count;
}

int BrushSettings::getScatterMaxCountAsInteger() const {
  return scatterMaxCount;
}

void BrushSettings::setScatterMaxCount(const int count) {
  this->scatterMaxCount = count;
}
