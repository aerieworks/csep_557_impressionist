//
// pointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "pointBrush.h"

extern float frand();

PointBrush::PointBrush(ImpressionistDoc* pDoc, char* name) :
ImpBrush(pDoc, name) {
}

Area* PointBrush::getModifiedArea(const Point brushLocation) {

  const int pointSize = getSettings()->getSizeAsInteger();
  const int offset = ceil(pointSize / 2) + 1;
  const int x = max(0, brushLocation.x - offset);
  const int y = max(0, brushLocation.y - offset);
  return new Area(x, y, offset * 2, offset * 2);
}

Area* PointBrush::brushBegin(const Point source, const Point target) {
  glPointSize(getSettings()->getSizeAsFloat());
  return brushMove(source, target);
}

Area* PointBrush::brushMove(const Point source, const Point target) {
  ImpressionistDoc* pDoc = getDocument();
  ImpressionistUI* dlg = pDoc->m_pUI;

  glBegin(GL_POINTS);
  setColor(source);

  glVertex2d(target.x, target.y);

  glEnd();

  return getModifiedArea(target);
}

Area* PointBrush::brushEnd(const Point source, const Point target) {
  // Nothing to do.
  return NULL;
}

