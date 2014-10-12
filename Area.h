#pragma once

class Area
{
public:
	Area(const int x, const int y, const int width, const int height);

	int GetX() const;
	int GetY() const;
	int GetWidth() const;
	int GetHeight() const;
private:
	const int x, y, width, height;
};
