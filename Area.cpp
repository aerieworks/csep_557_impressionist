#include "Area.h"

Area::Area(const int x, const int y, const int width, const int height)
	: x(x), y(y), width(width), height(height)
{
}

int Area::GetX() const
{
	return x;
}

int Area::GetY() const
{
	return y;
}

int Area::GetWidth() const
{
	return width;
}

int Area::GetHeight() const
{
	return height;
}
