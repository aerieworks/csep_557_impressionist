#include "BrushMoveAction.h"
#include "../Log.h"

bool BrushMoveAction::doAction() {
  Log::Debug << "Brush move." << Log::end;
  stroke->paint(source, target);
  return false;
}