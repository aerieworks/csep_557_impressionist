#include "BrushMoveAction.h"


BrushMoveAction::BrushMoveAction(ImpBrush* brush, const Point source, const Point target)
	: BrushAction(brush, source, target)
{
}

Area* BrushMoveAction::DoAction()
{
	return brush->BrushMove(source, target);
}