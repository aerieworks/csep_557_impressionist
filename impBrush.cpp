//
// impBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "impBrush.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount = 0;
ImpBrush**	ImpBrush::c_pBrushes = NULL;

ImpBrush::ImpBrush(ImpressionistDoc*	pDoc,
  char*				name) :
  m_pDoc(pDoc),
  m_pBrushName(name),
  m_settings() {

}

//---------------------------------------------------
// Return m_pDoc, which connects the UI and brushes
//---------------------------------------------------
ImpressionistDoc* ImpBrush::getDocument(void) {
  return m_pDoc;
}

//---------------------------------------------------
// Return the name of the current brush
//---------------------------------------------------
char* ImpBrush::getBrushName(void) {
  return m_pBrushName;
}

//----------------------------------------------------
// Return the settings object for the brush
//----------------------------------------------------
BrushSettings* ImpBrush::getSettings() {
  return &m_settings;
}

//----------------------------------------------------
// Set the color to paint with to the color at source,
// which is the coord at the original window to sample 
// the color from
//----------------------------------------------------
void ImpBrush::setColor(const Point source) {
  ImpressionistDoc* pDoc = getDocument();


  GLubyte color[4];

  memcpy(color, pDoc->getOriginalPixel(source), 3);
  color[3] = getSettings()->getOpacityAsChar();
  glColor4ubv(color);

}
