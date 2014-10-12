#include "Log.h"
#include "UndoItem.h"
#include "actions/DrawPixelsAction.h"

UndoItem::UndoItem(const char* name, Area* area, GLubyte* before, GLubyte* after)
	: name(name), area(area), before(before), after(after)
{
}

UndoItem::~UndoItem()
{
	Log::Debug << "Deleting UndoItem " << GetName() << ": (" << area->GetX() << ", " << area->GetY() << ")" << Log::end;
	delete area;
	delete[] before;
	delete[] after;
}

Action* UndoItem::GetRedoAction() const
{
	return new DrawPixelsAction(area, after);
}

Action* UndoItem::GetUndoAction() const
{
	return new DrawPixelsAction(area, before);
}

const char* UndoItem::GetName() const
{
	return name;
}
