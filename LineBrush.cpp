#include "impressionistDoc.h"
#include "KernelFilter.h"
#include "LineBrush.h"
#include "Log.h"

const double LineBrush::sobelXMatrix[9] { -1, 0, 1, -2, 0, 2, -1, 0, 1 };
const double LineBrush::sobelYMatrix[9] { 1, 2, 1, 0, 0, 0, -1, -2, -1 };
const KernelFilter LineBrush::sobelOperatorX(3, 3, sobelXMatrix, 1, 0);
const KernelFilter LineBrush::sobelOperatorY(3, 3, sobelYMatrix, 1, 0);

void LineBrush::LineBrushStroke::begin() {
  glLineWidth(settings->getLineWidthAsFloat());
}

void LineBrush::LineBrushStroke::resolveSettings(BrushSettings* settings, const Point source) const {
  if (settings->getBrushDirectionMode() == DirectionMode::Gradient) {
    settings->setBrushDirection(calculateDirection(source));
    settings->setBrushDirectionMode(DirectionMode::FixedDirection);
  } else if (settings->getBrushDirectionMode() == DirectionMode::Random) {
    settings->setBrushDirection(getRandomOffset(0, 360));
    settings->setBrushDirectionMode(DirectionMode::Random);
  }

  BrushStroke::resolveSettings(settings, source);
}

void LineBrush::LineBrushStroke::doPaint(const BrushSettings* settings, const Point source, const Point target) {
  int lineLength = settings->getSizeAsInteger();

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glTranslated(target.x, target.y, 0);
  glRotated(settings->getBrushDirectionAsDouble(), 0, 0, 1);

  glBegin(GL_LINES); {
    glColor4ubv(settings->getColor());

    glVertex2d(-lineLength / 2.0, 0);
    glVertex2d(lineLength / 2.0, 0);
  } glEnd();

  glPopMatrix();
}

double LineBrush::LineBrushStroke::calculateDirection(const Point source) const {
  const double xGradient = LineBrush::sobelOperatorX.evaluateAt(doc->m_ucLuminance, source.x, source.y, doc->m_nPaintWidth, doc->m_nPaintHeight, 1);
  const double yGradient = LineBrush::sobelOperatorY.evaluateAt(doc->m_ucLuminance, source.x, source.y, doc->m_nPaintWidth, doc->m_nPaintHeight, 1);
  const double angle = 90 + 180 * atan2(yGradient, xGradient) / PI;
  return angle;
}

ImpBrush::BrushStroke* LineBrush::createStroke() {
  return new LineBrush::LineBrushStroke(getDocument(), getSettings());
}
