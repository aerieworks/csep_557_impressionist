#include "BrushMoveAction.h"

bool BrushMoveAction::doAction() {
  stroke->paint(source, target);
  return false;
}