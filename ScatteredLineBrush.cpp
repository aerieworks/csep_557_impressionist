#include "ScatteredLineBrush.h"


ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc * pDoc, char * name) :
	LineBrush(pDoc, name), Scattered()
{
}


Area* ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	Point scatteredTarget = Scattered::GetScatteredTarget(target);
	return LineBrush::BrushMove(source, scatteredTarget);
}
