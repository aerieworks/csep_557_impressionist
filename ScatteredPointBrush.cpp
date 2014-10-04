#include "ScatteredPointBrush.h"


ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc * pDoc, char * name) :
	PointBrush(pDoc, name), Scattered()
{

}


void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	Point scatteredTarget = Scattered::GetScatteredTarget(target);
	PointBrush::BrushMove(source, scatteredTarget);
}
