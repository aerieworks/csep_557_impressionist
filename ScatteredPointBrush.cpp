#include "ScatteredPointBrush.h"


ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc * pDoc, char * name)
  : PointBrush(pDoc, name), Scattered() {
}


Area* ScatteredPointBrush::brushMove(const Point source, const Point target) {
  Point scatteredTarget = Scattered::getScatteredTarget(target);
  return PointBrush::brushMove(source, scatteredTarget);
}
