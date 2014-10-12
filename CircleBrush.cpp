#include <math.h>
#include "impressionistDoc.h"
#include "CircleBrush.h"

#define PI 3.1415926535897932384626433832795
#define CIRCLE_SEGMENT_FACTOR 0.01

CircleBrush::CircleBrush(ImpressionistDoc * pDoc, char * name)
  : ImpBrush(pDoc, name) {
}


Area* CircleBrush::getModifiedArea(const Point brushLocation) {
  const int pointSize = getSettings()->getSizeAsInteger();
  const int offset = ceil(pointSize / 2) + 1;
  const int x = max(0, brushLocation.x - offset);
  const int y = max(0, brushLocation.y - offset);
  return new Area(x, y, offset * 2, offset * 2);
}

Area* CircleBrush::brushBegin(const Point source, const Point target) {
  glPolygonMode(GL_FRONT, GL_FILL);
  return brushMove(source, target);
}

Area* CircleBrush::brushMove(const Point source, const Point target) {
  double radius = getSettings()->getSizeAsDouble() / 2;

  double vertexCount = 2 * radius * PI / CIRCLE_SEGMENT_FACTOR;

  glBegin(GL_POLYGON);
  setColor(source);

  for (double i = 0; i < 2 * PI; i += PI / vertexCount) {
    glVertex2d(target.x + cos(i) * radius, target.y + sin(i) * radius);
  }

  glEnd();
  return getModifiedArea(target);
}

Area* CircleBrush::brushEnd(const Point source, const Point target) {
  // Nothing to do.
  return NULL;
}
