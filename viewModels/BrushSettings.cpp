#include "BrushSettings.h"

#define DEFAULT_SIZE 20
#define DEFAULT_OPACITY 255

BrushSettings::BrushSettings()
	: size(DEFAULT_SIZE),
	  opacity(DEFAULT_OPACITY)
{
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