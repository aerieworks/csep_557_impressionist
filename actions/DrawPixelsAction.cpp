#include "DrawPixelsAction.h"

DrawPixelsAction::DrawPixelsAction(const Area* area, const unsigned char* pixels)
	: area(area), pixels(pixels), Action()
{
}

Area* DrawPixelsAction::DoAction()
{
	glPixelStorei(GL_UNPACK_ROW_LENGTH, area->GetWidth());
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glRasterPos2i(area->GetX(), area->GetY());
	glDrawPixels(area->GetWidth(), area->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE, (void*)pixels);
	return NULL;
}
