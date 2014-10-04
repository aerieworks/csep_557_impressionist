#include "BrushSettings.h"

#define DEFAULT_SIZE 20

BrushSettings::BrushSettings()
	: size(DEFAULT_SIZE)
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