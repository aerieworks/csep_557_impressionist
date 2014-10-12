#include "Log.h"
#include "UndoItem.h"
#include "actions/DrawPixelsAction.h"

UndoItem::UndoItem(const char* name, Area* area, GLubyte* before, GLubyte* after)
  : name(name), area(area), before(before), after(after) {
}

UndoItem::~UndoItem() {
  Log::Debug << "Deleting UndoItem " << getName() << ": (" << area->getX() << ", " << area->getY() << ")" << Log::end;
  delete area;
  delete[] before;
  delete[] after;
}

Action* UndoItem::getRedoAction() const {
  return new DrawPixelsAction(area, after);
}

Action* UndoItem::getUndoAction() const {
  return new DrawPixelsAction(area, before);
}

const char* UndoItem::getName() const {
  return name;
}
