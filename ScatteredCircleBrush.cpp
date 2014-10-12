#include "impressionistDoc.h"
#include "ScatteredCircleBrush.h"

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc * pDoc, char * name)
  : CircleBrush(pDoc, name), Scattered() {
}

Area* ScatteredCircleBrush::brushMove(const Point source, const Point target) {
  Point scatteredTarget = Scattered::getScatteredTarget(target);
  return CircleBrush::brushMove(source, scatteredTarget);
}
