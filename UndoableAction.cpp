#include "Log.h"
#include "UndoableAction.h"

UndoableAction::UndoableAction(const char* name, const unsigned char* current, const int width, const int height)
  : name(name),
    size(width * height * 3) {
  before = new unsigned char[size];
  memcpy(before, current, size);
}

UndoableAction::~UndoableAction() {
  Log::Debug << "Deleting UndoableAction " << getName() << Log::end;
  delete[] before;
}

void UndoableAction::undoAction(unsigned char* painting) const {
  Log::Debug << "Copying before to painting..." << Log::end;
  memcpy(painting, before, size);
  Log::Debug << "...done." << Log::end;
}

const char* UndoableAction::getName() const {
  return name;
}
