#include <math.h>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "CircleBrush.h"

#define PI 3.1415926535897932384626433832795
#define CIRCLE_SEGMENT_FACTOR 0.01

CircleBrush::CircleBrush(ImpressionistDoc *pDoc, char *name) :
	ImpBrush(pDoc, name)
{
}


void CircleBrush::BrushBegin(const Point source, const Point target)
{
	glPolygonMode(GL_FRONT, GL_FILL);
	BrushMove(source, target);
}

void CircleBrush::BrushMove(const Point source, const Point target)
{
	ImpressionistDoc* pDoc = GetDocument();
	double radius = pDoc->getSize() / 2;

	double vertexCount = 2 * radius * PI / CIRCLE_SEGMENT_FACTOR;

	glBegin(GL_POLYGON);
		SetColor(source);
		
		for (double i = 0; i < 2 * PI; i += PI / vertexCount) {
			glVertex2d(target.x + cos(i) * radius, target.y + sin(i) * radius);
		}

	glEnd();
}

void CircleBrush::BrushEnd(const Point source, const Point target)
{

}
