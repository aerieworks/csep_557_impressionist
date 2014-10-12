#include "impressionistDoc.h"
#include "KernelFilter.h"
#include "LineBrush.h"
#include "Log.h"

LineBrush::LineBrush(ImpressionistDoc * pDoc, char * name)
  : ImpBrush(pDoc, name) {
  double sobelXMatrix[9] { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
  double sobelYMatrix[9] { 1, 2, 1, 0, 0, 0, -1, -2, -1 };
  sobelOperatorX = new KernelFilter(3, 3, sobelXMatrix, 1, 0);
  sobelOperatorY = new KernelFilter(3, 3, sobelYMatrix, 1, 0);
}

LineBrush::~LineBrush() {
  delete sobelOperatorX;
  delete sobelOperatorY;
}

double LineBrush::calculateDirection(const Point source) {
  if (getSettings()->getBrushDirectionMode() == DirectionMode::Fixed) {
    return getSettings()->getBrushDirectionAsDouble();
  } else {
    const double xGradient = sobelOperatorX->evaluateAt(getDocument()->m_ucLuminance, source.x, source.y, getDocument()->m_nPaintWidth, getDocument()->m_nPaintHeight, 1);
    const double yGradient = sobelOperatorY->evaluateAt(getDocument()->m_ucLuminance, source.x, source.y, getDocument()->m_nPaintWidth, getDocument()->m_nPaintHeight, 1);
    const double angle = 180 * (atan2(yGradient, xGradient) + 90) / PI;
    Log::Debug << "Gradient at (" << source.x << ", " << source.y << "): " << xGradient << " x " << yGradient << ": " << angle << Log::end;
    return angle;
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
  glRotated(calculateDirection(source), 0, 0, 1);

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