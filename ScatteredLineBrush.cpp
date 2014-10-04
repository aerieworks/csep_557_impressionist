#include "ScatteredLineBrush.h"


ScatteredLineBrush::ScatteredLineBrush(ImpressionistDoc * pDoc, char * name) :
	LineBrush(pDoc, name), Scattered()
{
}


void ScatteredLineBrush::BrushMove(const Point source, const Point target)
{
	Point scatteredTarget = Scattered::GetScatteredTarget(target);
	LineBrush::BrushMove(source, scatteredTarget);
}