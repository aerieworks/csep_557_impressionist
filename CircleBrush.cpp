#include <math.h>
#include "impressionistDoc.h"
#include "CircleBrush.h"

#define CIRCLE_SEGMENT_FACTOR 0.01

void CircleBrush::CircleBrushStroke::begin() {
  glPolygonMode(GL_FRONT, GL_FILL);
}

void CircleBrush::CircleBrushStroke::doPaint(const BrushSettings* settings, const Point source, const Point target) {
  double radius = settings->getSizeAsDouble() / 2;

  double vertexCount = 2 * radius * PI / CIRCLE_SEGMENT_FACTOR;

  glBegin(GL_POLYGON); {
    glColor4ubv(settings->getColor());
    for (double i = 0; i < 2 * PI; i += PI / vertexCount) {
      glVertex2d(target.x + cos(i) * radius, target.y + sin(i) * radius);
    }
  } glEnd();
}

ImpBrush::BrushStroke* CircleBrush::createStroke() {
  return new CircleBrush::CircleBrushStroke(getDocument(), getSettings());
}
