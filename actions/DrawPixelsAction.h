#pragma once
#include <Windows.h>
#include <gl/GL.h>
#include "Action.h"
class DrawPixelsAction :
	public Action
{
public:
	DrawPixelsAction(const Area* area, const GLubyte* pixels);

	Area* DoAction();

private:
	const Area* area;
	const GLubyte* pixels;
};

