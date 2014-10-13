//
// pointBrush.cpp
//
// The implementation of Point Brush. It is a kind of ImpBrush. All your brush implementations
// will look like the file with the different GL primitive calls.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "pointBrush.h"
#include "Log.h"

extern float frand();

void PointBrush::PointBrushStroke::begin() {
  Log::Debug << "PointBrushStroke::begin" << Log::end;
  glPointSize(settings->getSizeAsFloat());
}

void PointBrush::PointBrushStroke::doPaint(const BrushSettings* settings, const Point source, const Point target) {
  Log::printSettings(settings);
  glBegin(GL_POINTS); {
    glColor4ubv(settings->getColor());
    glVertex2d(target.x, target.y);
  } glEnd();
}

ImpBrush::BrushStroke* PointBrush::createStroke() {
  return new PointBrush::PointBrushStroke(getDocument(), getSettings());
}