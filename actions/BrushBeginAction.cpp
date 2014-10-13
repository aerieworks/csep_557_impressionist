#include "BrushBeginAction.h"


bool BrushBeginAction::doAction() {
  stroke->begin();
  stroke->paint(source, target);
  return false;
}