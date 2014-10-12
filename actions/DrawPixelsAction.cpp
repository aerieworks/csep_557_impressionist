#include "DrawPixelsAction.h"

DrawPixelsAction::DrawPixelsAction(const Area* area, const unsigned char* pixels)
  : area(area), pixels(pixels), Action() {
}

Area* DrawPixelsAction::doAction() {
  glPixelStorei(GL_UNPACK_ROW_LENGTH, area->getWidth());
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glRasterPos2i(area->getX(), area->getY());
  glDrawPixels(area->getWidth(), area->getHeight(), GL_RGB, GL_UNSIGNED_BYTE, (void*)pixels);
  return NULL;
}
