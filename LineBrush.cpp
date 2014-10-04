#include "impressionistDoc.h"
#include "LineBrush.h"


LineBrush::LineBrush(ImpressionistDoc * pDoc, char * name) :
ImpBrush(pDoc, name)
{
}

void LineBrush::BrushBegin(const Point source, const Point target)
{
	BrushMove(source, target);
}

void LineBrush::BrushMove(const Point source, const Point target)
{
	int lineLength = GetSettings()->GetSizeAsInteger();

	glBegin(GL_LINES);
		SetColor(source);
		
		glVertex2d(target.x - lineLength / 2.0, target.y);
		glVertex2d(target.x + lineLength / 2.0, target.y);
	glEnd();
}

void LineBrush::BrushEnd(const Point source, const Point target)
{

}