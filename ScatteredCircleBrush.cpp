#include "impressionistDoc.h"
#include "ScatteredCircleBrush.h"


using namespace std;

ScatteredCircleBrush::ScatteredCircleBrush(ImpressionistDoc * pDoc, char * name) :
	CircleBrush(pDoc, name), Scattered()
{
}

void ScatteredCircleBrush::BrushMove(const Point source, const Point target)
{
	Point scatteredTarget = Scattered::getScatteredTarget(target);
	CircleBrush::BrushMove(source, scatteredTarget);
}
