//
// paintview.h
//
// The header file for painting view of the input images
//

#ifndef PAINTVIEW_H
#define PAINTVIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Gl_Window.H>
#include <FL/gl.h>
#ifdef __APPLE__
#include <OpenGL/glu.h>
#else
#include <GL/glu.h>
#endif
#include <stdlib.h>
#include "actions/Action.h"
#include "Area.h"

class ImpressionistDoc;

class PaintView : public Fl_Gl_Window {
public:
  PaintView(int x, int y, int w, int h, const char* l);
  void draw();
  void handleAction(Action* action);
  int handle(int event);

  void refresh();

  void resizeWindow(int width, int height);

  void saveCurrentContent();

  void restoreContent();

  ImpressionistDoc *m_pDoc;

private:
  void addUndoFor(Area* invalidatedArea);

  GLvoid* m_pPaintBitstart;
  Action* m_actionToDo;
  int		m_nDrawWidth,
    m_nDrawHeight,
    m_nStartRow,
    m_nEndRow,
    m_nStartCol,
    m_nEndCol,
    m_nWindowWidth,
    m_nWindowHeight;

};

#endif

