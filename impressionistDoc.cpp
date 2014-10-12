// 
// impressionistDoc.cpp
//
// It basically maintain the Image for answering the color query from the brush.
// It also acts as the bridge between brushes and UI (including views)
//


#include <FL/fl_ask.H>

#include <algorithm>
#include <sstream>
#include "impressionistDoc.h"
#include "impressionistUI.h"

#include "impBrush.h"

// Include individual brush headers here.
#include "CircleBrush.h"
#include "LineBrush.h"
#include "Log.h"
#include "pointBrush.h"
#include "ScatteredCircleBrush.h"
#include "ScatteredLineBrush.h"
#include "ScatteredPointBrush.h"


#define DESTROY(p)	{  if ((p)!=NULL) {delete [] p; p=NULL; } }

ImpressionistDoc::ImpressionistDoc() {
  // Set NULL image name as init. 
  m_imageName[0] = '\0';

  m_nWidth = -1;
  m_ucImage = NULL;
  m_ucPainting = NULL;
  m_ucPreviewBackup = NULL;


  // create one instance of each brush
  ImpBrush::c_nBrushCount = NUM_BRUSH_TYPE;
  ImpBrush::c_pBrushes = new ImpBrush*[ImpBrush::c_nBrushCount];

  ImpBrush::c_pBrushes[BRUSH_POINTS] = new PointBrush(this, "Points");

  // Note: You should implement these 5 brushes.  They are set the same (PointBrush) for now
  ImpBrush::c_pBrushes[BRUSH_LINES]
    = new LineBrush(this, "Lines");
  ImpBrush::c_pBrushes[BRUSH_CIRCLES]
    = new CircleBrush(this, "Circles");
  ImpBrush::c_pBrushes[BRUSH_SCATTERED_POINTS]
    = new ScatteredPointBrush(this, "Scattered Points");
  ImpBrush::c_pBrushes[BRUSH_SCATTERED_LINES]
    = new ScatteredLineBrush(this, "Scattered Lines");
  ImpBrush::c_pBrushes[BRUSH_SCATTERED_CIRCLES]
    = new ScatteredCircleBrush(this, "Scattered Circles");

  // make one of the brushes current
  m_pCurrentBrush = ImpBrush::c_pBrushes[0];

}

ImpressionistDoc::~ImpressionistDoc() {
  // Empty and deallocate the undo and redo stacks.
  clearStack(m_undoStack);
  clearStack(m_redoStack);
}

//---------------------------------------------------------
// Set the current UI 
//---------------------------------------------------------
void ImpressionistDoc::setUI(ImpressionistUI* ui) {
  m_pUI = ui;
}

//---------------------------------------------------------
// Returns the active picture/painting name
//---------------------------------------------------------
char* ImpressionistDoc::getImageName() {
  return m_imageName;
}

//---------------------------------------------------------
// Called by the UI when the user changes the brush type.
// type: one of the defined brush types.
//---------------------------------------------------------
void ImpressionistDoc::setBrushType(int type) {
  m_pCurrentBrush = ImpBrush::c_pBrushes[type];
}

//---------------------------------------------------------
// Load the specified image
// This is called by the UI when the load image button is 
// pressed.
//---------------------------------------------------------
int ImpressionistDoc::loadImage(const char *iname) {
  // try to open the image to read
  unsigned char*	data;
  int				width,
    height;

  if ((data = load(iname, width, height)) == NULL) {
    fl_alert("Can't load image file");
    return 0;
  }

  // reflect the fact of loading the new image
  m_nWidth = width;
  m_nPaintWidth = width;
  m_nHeight = height;
  m_nPaintHeight = height;

  // release old storage
  delete[] m_ucImage;
  delete[] m_ucPainting;
  delete[] m_ucPreviewBackup;

  m_ucImage = data;

  // allocate space for draw view
  m_ucPainting = new unsigned char[width*height * 3];
  m_ucPreviewBackup = new unsigned char[width*height * 3];
  memset(m_ucPainting, 0, width*height * 3);

  m_pUI->m_mainWindow->resize(m_pUI->m_mainWindow->x(),
    m_pUI->m_mainWindow->y(),
    width * 2,
    height + 25);

  // display it on origView
  m_pUI->m_origView->resizeWindow(width, height);
  m_pUI->m_origView->refresh();

  // refresh paint view as well
  m_pUI->m_paintView->resizeWindow(width, height);
  m_pUI->m_paintView->refresh();


  return 1;
}


//----------------------------------------------------------------
// Save the specified image
// This is called by the UI when the save image menu button is 
// pressed.
//----------------------------------------------------------------
int ImpressionistDoc::saveImage(const char *iname, const char * type, int quality) {

  save(iname, m_ucPainting, m_nPaintWidth, m_nPaintHeight, type, quality);

  return 1;
}

//----------------------------------------------------------------
// Clear the drawing canvas
// This is called by the UI when the clear canvas menu item is 
// chosen
//-----------------------------------------------------------------
int ImpressionistDoc::clearCanvas() {

  // Release old storage
  if (m_ucPainting) {
    delete[] m_ucPainting;

    // allocate space for draw view
    m_ucPainting = new unsigned char[m_nPaintWidth*m_nPaintHeight * 3];
    memset(m_ucPainting, 0, m_nPaintWidth*m_nPaintHeight * 3);

    // refresh paint view as well	
    m_pUI->m_paintView->refresh();
  }

  return 0;
}

// Apply the filter specified by filter to each pixel in either the painting
// or the original image and place the resulting value in the painting buffer.
// pixel in the destination buffer.  
void ImpressionistDoc::applyFilter(const KernelFilter& filter, const bool applyToPainting) {
  const unsigned char* source;
  if (applyToPainting) {
    // If applying to the painting, get the source value from the preview buffer.
    source = m_ucPreviewBackup;
  } else {
    // If applying to the source image, get the source value from the source image.
    source = m_ucImage;
  }

  filter.apply(source, m_ucPainting, m_nPaintWidth, m_nPaintHeight);
}

//------------------------------------------------------------------
// Get the color of the pixel in the original image at coord x and y
//------------------------------------------------------------------
GLubyte* ImpressionistDoc::getOriginalPixel(int x, int y) {
  if (x < 0)
    x = 0;
  else if (x >= m_nWidth)
    x = m_nWidth - 1;

  if (y < 0)
    y = 0;
  else if (y >= m_nHeight)
    y = m_nHeight - 1;

  return (GLubyte*)(m_ucImage + 3 * (y*m_nWidth + x));
}

//----------------------------------------------------------------
// Get the color of the pixel in the original image at point p
//----------------------------------------------------------------
GLubyte* ImpressionistDoc::getOriginalPixel(const Point p) {
  return getOriginalPixel(p.x, p.y);
}


void ImpressionistDoc::clearStack(std::stack<UndoItem*>& st) {
  while (!st.empty()) {
    UndoItem* item = st.top();
    delete item;
    st.pop();
  }
}

//----------------------------------------------------------------
// Performs the action and adds it to the undo queue.
//----------------------------------------------------------------
void ImpressionistDoc::addUndoItem(UndoItem* item) {
  m_undoStack.push(item);
  // Clear the redo stack when new actions are performed.
  clearStack(m_redoStack);
}

//----------------------------------------------------------------
// Gets whether or not there is an action that can be undone.
//----------------------------------------------------------------
bool ImpressionistDoc::canUndo() const {
  return !m_undoStack.empty();
}

//----------------------------------------------------------------
// Gets whether or not there is an action that can be redone.
//----------------------------------------------------------------
bool ImpressionistDoc::canRedo() const {
  return !m_redoStack.empty();
}

//----------------------------------------------------------------
// Undoes the most recent action.
//----------------------------------------------------------------
void ImpressionistDoc::undo() {
  if (canUndo()) {
    UndoItem* item = m_undoStack.top();
    Log::Debug << "Doc: Undoing " << item->getName() << Log::end;
    m_pUI->m_paintView->handleAction(item->getUndoAction());
    m_redoStack.push(item);
    m_undoStack.pop();
  } else {
    Log::Debug << "Nothing to undo." << Log::end;
  }
}

//----------------------------------------------------------------
// Redoes the most recent action.
//----------------------------------------------------------------
void ImpressionistDoc::redo() {
  if (canRedo()) {
    UndoItem* item = m_redoStack.top();
    Log::Debug << "Doc: Redoing " << item->getName() << Log::end;
    m_pUI->m_paintView->handleAction(item->getRedoAction());
    m_undoStack.push(item);
    m_redoStack.pop();
  } else {
    Log::Debug << "Nothing to redo." << Log::end;
  }
}
