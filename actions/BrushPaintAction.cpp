#include "BrushPaintAction.h"
#include "../Log.h"

BrushPaintAction::~BrushPaintAction() {
  Log::Debug << "Deleting brush paint action." << Log::end;
  delete stroke;
}

bool BrushPaintAction::doAction() {
  stroke->replay();
  return true;
}
