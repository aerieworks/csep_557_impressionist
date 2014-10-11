#include "BrushSettings.h"

#define DEFAULT_LINE_WIDTH 1
#define DEFAULT_OPACITY 255
#define DEFAULT_SIZE 20
#define DEFAULT_BRUSH_DIRECTION 0

BrushSettings::BrushSettings()
	: lineWidth(DEFAULT_LINE_WIDTH),
	  opacity(DEFAULT_OPACITY),
	  size(DEFAULT_SIZE),
	  brushDirection(DEFAULT_BRUSH_DIRECTION)
{
}

double BrushSettings::GetLineWidthAsDouble() const
{
	return lineWidth;
}

float BrushSettings::GetLineWidthAsFloat() const
{
	return (float)lineWidth;
}

void BrushSettings::SetLineWidth(const double lineWidth)
{
	this->lineWidth = lineWidth;
}

char BrushSettings::GetOpacityAsChar() const
{
	return (char)opacity;
}

double BrushSettings::GetOpacityAsDouble() const
{
	return opacity;
}

void BrushSettings::SetOpacity(const double opacity)
{
	this->opacity = opacity;
}

int BrushSettings::GetSizeAsInteger() const
{
	return size;
}

double BrushSettings::GetSizeAsDouble() const
{
	return (double)size;
}

float BrushSettings::GetSizeAsFloat() const
{
	return (float)size;
}

void BrushSettings::SetSize(const int size)
{
	this->size = size;
}

double BrushSettings::GetBrushDirectionAsDouble() const
{
	return brushDirection;
}

void BrushSettings::SetBrushDirection(const double brushDirection)
{
	this->brushDirection = brushDirection;
}
