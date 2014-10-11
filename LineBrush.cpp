#include "impressionistDoc.h"
#include "LineBrush.h"
#include "Log.h"


LineBrush::LineBrush(ImpressionistDoc * pDoc, char * name) :
ImpBrush(pDoc, name)
{
}

Area* LineBrush::BrushBegin(const Point source, const Point target)
{
	glLineWidth(GetSettings()->GetLineWidthAsFloat());
	return BrushMove(source, target);
}

Area* LineBrush::BrushMove(const Point source, const Point target)
{
	int lineLength = GetSettings()->GetSizeAsInteger();

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glTranslated(target.x, target.y, 0);
	glRotated(GetSettings()->GetBrushDirectionAsDouble(), 0, 0, 1);

	glBegin(GL_LINES);
		SetColor(source);
		
		glVertex2d(-lineLength / 2.0, 0);
		glVertex2d(lineLength / 2.0, 0);
	glEnd();

	glPopMatrix();

	const float lineWidth = GetSettings()->GetLineWidthAsFloat();
	return new Area(target.x - ceil(lineLength / 2.0), target.y - ceil(lineWidth / 2), lineLength, (int)ceil(lineWidth));
}

Area* LineBrush::BrushEnd(const Point source, const Point target)
{
	// Nothing to do.
	return NULL;
}