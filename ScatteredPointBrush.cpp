#include "ScatteredPointBrush.h"


ScatteredPointBrush::ScatteredPointBrush(ImpressionistDoc * pDoc, char * name) :
	PointBrush(pDoc, name), Scattered()
{

}


Area* ScatteredPointBrush::BrushMove(const Point source, const Point target)
{
	Point scatteredTarget = Scattered::GetScatteredTarget(target);
	return PointBrush::BrushMove(source, scatteredTarget);
}
