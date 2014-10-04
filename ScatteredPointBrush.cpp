#include "ScatteredPointBrush.h"


ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc * pDoc, char * name) :
	PointBrush(pDoc, name), Scattered()
{

}


void ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	Point scatteredTarget = Scattered::getScatteredTarget(target);
	PointBrush::BrushMove(source, scatteredTarget);
}
