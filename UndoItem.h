#ifndef UNDOITEM_H
#define UNDOITEM_H

#include <Windows.h>
#include <gl/GL.h>
#include "Area.h"

class Action;
class UndoItem {
public:
  UndoItem(const char* name, Area* area, GLubyte* before, GLubyte* after);
  ~UndoItem();

  Action* getRedoAction() const;
  Action* getUndoAction() const;
  const char* getName() const;
private:
  const char* name;
  Area* area;
  unsigned char* before;
  unsigned char* after;
};
#endif
