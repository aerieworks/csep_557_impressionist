#include "BrushEndAction.h"
#include "BrushPaintAction.h"


bool BrushEndAction::doAction() {
  stroke->end();
  doc->addUndoItem(new BrushPaintAction(doc->m_ucPainting, doc->m_nPaintWidth, doc->m_nPaintHeight, stroke));
  return true;
}