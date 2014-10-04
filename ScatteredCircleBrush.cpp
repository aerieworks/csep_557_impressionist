#include "impressionistDoc.h"
#include "ScatteredCircleBrush.h"

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc * pDoc, char * name) :
	CircleBrush(pDoc, name), Scattered()
{
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	Point scatteredTarget = Scattered::GetScatteredTarget(target);
	CircleBrush::BrushMove(source, scatteredTarget);
}
