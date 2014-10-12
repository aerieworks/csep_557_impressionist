#include "BrushEndAction.h"


BrushEndAction::BrushEndAction(ImpBrush* brush, const Point source, const Point target)
	: BrushAction(brush, source, target)
{
}

Area* BrushEndAction::DoAction()
{
	return brush->BrushEnd(source, target);
}