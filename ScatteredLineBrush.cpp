#include "ScatteredLineBrush.h"


ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc * pDoc, char * name)
  : LineBrush(pDoc, name), Scattered() {
}


Area* ScatteredLineBrush::brushMove(const Point source, const Point target) {
  Point scatteredTarget = Scattered::getScatteredTarget(target);
  return LineBrush::brushMove(source, scatteredTarget);
}
