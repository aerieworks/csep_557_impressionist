#pragma once

class Area {
public:
  Area(const int x, const int y, const int width, const int height);

  int getX() const;
  int getY() const;
  int getWidth() const;
  int getHeight() const;
private:
  const int x, y, width, height;
};
