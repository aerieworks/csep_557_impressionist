#include "impressionistDoc.h"
#include "KernelFilter.h"
#include "LineBrush.h"
#include "Log.h"


LineBrush::LineBrush(ImpressionistDoc * pDoc, char * name) :
ImpBrush(pDoc, name) {
}

double LineBrush::calculateDirection() {
  if (getSettings()->getBrushDirectionMode() == DirectionMode::Fixed) {
    return getSettings()->getBrushDirectionAsDouble();
  } else {
    return 0;
  }
}

Area* LineBrush::brushBegin(const Point source, const Point target) {
  glLineWidth(getSettings()->getLineWidthAsFloat());
  return brushMove(source, target);
}

Area* LineBrush::brushMove(const Point source, const Point target) {
  int lineLength = getSettings()->getSizeAsInteger();

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated(target.x, target.y, 0);
  glRotated(calculateDirection(), 0, 0, 1);

  glBegin(GL_LINES);
  setColor(source);

  glVertex2d(-lineLength / 2.0, 0);
  glVertex2d(lineLength / 2.0, 0);
  glEnd();

  glPopMatrix();

  const float lineWidth = getSettings()->getLineWidthAsFloat();
  return new Area(target.x - ceil(lineLength / 2.0), target.y - ceil(lineWidth / 2), lineLength, (int)ceil(lineWidth));
}

Area* LineBrush::brushEnd(const Point source, const Point target) {
  // Nothing to do.
  return NULL;
}