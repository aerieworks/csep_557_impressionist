// 
// impressionistDoc.h
//
// header file for Doc 
//

#ifndef ImpressionistDoc_h
#define ImpressionistDoc_h

#include <stack>

#include "impressionist.h"
#include "imageio.h"
#include "KernelFilter.h"
#include "UndoItem.h"

class ImpressionistUI;

class ImpressionistDoc {
public:
  ImpressionistDoc();
  ~ImpressionistDoc();

  void	setUI(ImpressionistUI* ui);		// Assign the UI to use

  int		loadImage(const char *iname);			// called by the UI to load image
  int		saveImage(const char *iname, const char * type, int quality);// called by the UI to save image


  int     clearCanvas();                  // called by the UI to clear the drawing canvas

  void applyFilter(const KernelFilter& filter, const bool applyToPainting);
  void applyFilter(const unsigned char* sourceBuffer, //The filter kernel
    int srcBufferWidth, int srcBufferHeight,
    unsigned char* destBuffer,
    const double *filterKernel,
    int knlWidth, int knlHeight,
    double divisor, double offset);

  void	setBrushType(int type);			// called by the UI to set the brushType
  char*	getImageName();					// get the current image name


  // Attributes
public:
  // Dimensions of original window.
  int				m_nWidth,
    m_nHeight;
  // Dimensions of the paint window.
  int				m_nPaintWidth,
    m_nPaintHeight;
  // Images for original image and painting.
  unsigned char*	m_ucImage;
  unsigned char*	m_ucPainting;

  // Used by the filtering code so that we can
  // preview filters before applying.
  unsigned char*	m_ucPreviewBackup;

  // Luminance of the original image.  Used to evaluate Sobel operator.
  unsigned char* m_ucLuminance;



  // The current active brush.
  ImpBrush*			m_pCurrentBrush;
  // Size of the brush.
  int m_nSize;

  ImpressionistUI*	m_pUI;

  // Operations
public:
  // Get the color of the original picture at the specified coord
  GLubyte* getOriginalPixel(int x, int y);
  // Get the color of the original picture at the specified point	
  GLubyte* getOriginalPixel(const Point p);

  // Adds the item to the undo stack.
  void addUndoItem(UndoItem* item);
  // Gets whether or not there is an action that can be undone.
  bool canUndo() const;
  // Gets whether or not there is an action that can be redone.
  bool canRedo() const;
  // Undo the most recent action.
  void undo();
  // Redo the most recent action.
  void redo();

private:
  unsigned char* calculateLuminance(const unsigned char* source);
  void				clearStack(std::stack<UndoItem*>& s);
  char				m_imageName[256];
  std::stack<UndoItem*>	m_undoStack;
  std::stack<UndoItem*>	m_redoStack;
};

extern void MessageBox(char *message);

#endif
