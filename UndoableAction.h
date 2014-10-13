#ifndef UNDOITEM_H
#define UNDOITEM_H

#include <Windows.h>
#include <gl/GL.h>
#include "actions/Action.h"

class UndoableAction : public Action {
public:
  UndoableAction(const char* name, const unsigned char* current, const int width, const int height);
  ~UndoableAction();

  void undoAction(unsigned char* painting) const;
  const char* getName() const;
private:
  const char* name;
  const int size;
  unsigned char* before;
};
#endif
