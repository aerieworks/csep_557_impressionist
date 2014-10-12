//
// paintview.cpp
//
// The code maintaining the painting view of the input images
//

#include "Log.h"
#include "impressionist.h"
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "paintView.h"
#include "UndoItem.h"
#include "actions/BrushBeginAction.h"
#include "actions/BrushEndAction.h"
#include "actions/BrushMoveAction.h"


#define LEFT_MOUSE_DOWN		1
#define LEFT_MOUSE_DRAG		2
#define LEFT_MOUSE_UP		3
#define RIGHT_MOUSE_DOWN	4
#define RIGHT_MOUSE_DRAG	5
#define RIGHT_MOUSE_UP		6


#ifndef WIN32
#define min(a, b)	( ( (a)<(b) ) ? (a) : (b) )
#define max(a, b)	( ( (a)>(b) ) ? (a) : (b) )
#endif

PaintView::PaintView(int			x,
  int			y,
  int			w,
  int			h,
  const char*	l)
  : Fl_Gl_Window(x, y, w, h, l) {
  m_nWindowWidth = w;
  m_nWindowHeight = h;
  m_actionToDo = NULL;
}


void PaintView::draw() {
#ifndef MESA
#ifdef _WIN32
  // To avoid flicker on some machines.
  glDrawBuffer(GL_BACK);
#endif
#endif // !MESA

  if (!valid()) {


    glClearColor(0.7f, 0.7f, 0.7f, 1.0);

    // We're only using 2-D, so turn off depth 
    glDisable(GL_DEPTH_TEST);

    // Enable blending for opacity.
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ortho();

    int	cx = m_nWindowWidth = w();
    int	cy = m_nWindowHeight = h();



    // Tell openGL to read from the front buffer when capturing
    // out paint strokes
#ifdef _WIN32
    glReadBuffer(GL_FRONT);
#endif
    glViewport(0, 0, cx, cy);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, cx, 0, cy);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    // fun home activity:  what is this translation for?
    glTranslatef(0.375, 0.375, 0.0);


    glClear(GL_COLOR_BUFFER_BIT);
  }

  Point scrollpos;// = GetScrollPosition();
  scrollpos.x = 0;
  scrollpos.y = 0;

  m_nWindowWidth = w();
  m_nWindowHeight = h();

  int drawWidth, drawHeight;
  drawWidth = min(m_nWindowWidth, m_pDoc->m_nPaintWidth);
  drawHeight = min(m_nWindowHeight, m_pDoc->m_nPaintHeight);

  int startrow = m_pDoc->m_nPaintHeight - (scrollpos.y + drawHeight);
  if (startrow < 0) startrow = 0;

  m_pPaintBitstart = m_pDoc->m_ucPainting +
    3 * ((m_pDoc->m_nPaintWidth * startrow) + scrollpos.x);

  m_nDrawWidth = drawWidth;
  m_nDrawHeight = drawHeight;

  m_nStartRow = startrow;
  m_nEndRow = startrow + drawHeight;
  m_nStartCol = scrollpos.x;

  if (m_pDoc->m_ucPainting && m_actionToDo == NULL) {
    restoreContent();

  }



  if (m_pDoc->m_ucPainting && m_actionToDo) {
#ifndef _WIN32
    restoreContent();
#endif

    Area* modifiedArea = m_actionToDo->doAction();
    delete m_actionToDo;
    m_actionToDo = NULL;

#ifndef _WIN32
    saveCurrentContent();
#endif

    if (modifiedArea != NULL) {
      addUndoFor(modifiedArea);
    }
  }

  glFlush();

#ifndef MESA
#ifdef _WIN32
  // To avoid flicker on some machines.
  glDrawBuffer(GL_BACK);
#endif
#endif // !MESA

}

void PaintView::handleAction(Action* action) {
  m_actionToDo = action;
  redraw();
}

int PaintView::handle(int event) {
  Point scrollPos;// = GetScrollPosition();
  scrollPos.x = 0;
  scrollPos.y = 0;

  const int windowHeight = h();
  const int drawHeight = min(windowHeight, m_pDoc->m_nPaintHeight);
  const int startRow = max(0, m_pDoc->m_nPaintHeight - (scrollPos.y + drawHeight));
  const int endRow = startRow + drawHeight;
  const int startCol = scrollPos.x;

  Point mousePos = Point(Fl::event_x(), Fl::event_y());
  Point source(mousePos.x + scrollPos.x, endRow - mousePos.y);
  Point target(mousePos.x, windowHeight - mousePos.y);

  switch (event) {
  case FL_ENTER:
    //redraw();
    break;
  case FL_PUSH:
    if (Fl::event_button() == 1) {
      handleAction(new BrushBeginAction(m_pDoc->m_pCurrentBrush, source, target));
    }
    break;
  case FL_DRAG:
    if (Fl::event_button() == 1) {
      handleAction(new BrushMoveAction(m_pDoc->m_pCurrentBrush, source, target));
    }
    break;
  case FL_RELEASE:
    if (Fl::event_button() == 1) {
      handleAction(new BrushEndAction(m_pDoc->m_pCurrentBrush, source, target));
      saveCurrentContent();
      restoreContent();
    }
    break;
  default:
    return 0;
    break;

  }



  return 1;
}

void PaintView::refresh() {
  redraw();
}

void PaintView::resizeWindow(int width, int height) {
  resize(x(), y(), width, height);
}

void PaintView::saveCurrentContent() {
  // Tell openGL to read from the front buffer when capturing
  // out paint strokes
#ifdef _WIN32
  glReadBuffer(GL_FRONT);
#endif
  glPixelStorei(GL_PACK_ALIGNMENT, 1);
  glPixelStorei(GL_PACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);

  glReadPixels(0,
    m_nWindowHeight - m_nDrawHeight,
    m_nDrawWidth,
    m_nDrawHeight,
    GL_RGB,
    GL_UNSIGNED_BYTE,
    m_pPaintBitstart);
}


void PaintView::restoreContent() {
#ifdef _WIN32
  glDrawBuffer(GL_BACK);
#endif
  glClear(GL_COLOR_BUFFER_BIT);

  glRasterPos2i(0, m_nWindowHeight - m_nDrawHeight);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glPixelStorei(GL_UNPACK_ROW_LENGTH, m_pDoc->m_nPaintWidth);
  glDrawPixels(m_nDrawWidth,
    m_nDrawHeight,
    GL_RGB,
    GL_UNSIGNED_BYTE,
    m_pPaintBitstart);

  //	glDrawBuffer(GL_FRONT);
}

void PaintView::addUndoFor(Area* modifiedArea) {
  glPixelStorei(GL_PACK_ROW_LENGTH, modifiedArea->getWidth());
  glPixelStorei(GL_PACK_ALIGNMENT, 1);

  GLubyte* before = new GLubyte[3 * modifiedArea->getWidth() * modifiedArea->getHeight()];
  glReadBuffer(GL_FRONT);
  glReadPixels(modifiedArea->getX(), modifiedArea->getY(), modifiedArea->getWidth(), modifiedArea->getHeight(), GL_RGB, GL_UNSIGNED_BYTE, (void*)before);
  //Log::PrintPixels("Before for undo", modifiedArea, before, 3);

  GLubyte* after = new GLubyte[3 * modifiedArea->getWidth() * modifiedArea->getHeight()];
  glReadBuffer(GL_BACK);
  glReadPixels(modifiedArea->getX(), modifiedArea->getY(), modifiedArea->getWidth(), modifiedArea->getHeight(), GL_RGB, GL_UNSIGNED_BYTE, (void*)after);
  //Log::PrintPixels("After for redo", modifiedArea, after, 3);

  m_pDoc->addUndoItem(new UndoItem("Brush", modifiedArea, before, after));
}