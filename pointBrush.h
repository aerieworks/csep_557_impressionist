//
// pointBrush.h
//
// The header file for Point Brush. 
//

#ifndef POINTBRUSH_H
#define POINTBRUSH_H

#include "impBrush.h"

class PointBrush : public ImpBrush
{
public:
	PointBrush( ImpressionistDoc* pDoc = NULL, char* name = NULL );

	Area* BrushBegin( const Point source, const Point target );
	Area* BrushMove( const Point source, const Point target );
	Area* BrushEnd( const Point source, const Point target );
	char* BrushName( void );
private:
	Area* GetModifiedArea(const Point target);
};

#endif
