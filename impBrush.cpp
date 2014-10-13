//
// impBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "impBrush.h"
#include "Log.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount = 0;
ImpBrush**	ImpBrush::c_pBrushes = NULL;

ImpBrush::BrushStroke::~BrushStroke() {
  Log::Debug << "Deleting stroke." << Log::end;
  for (BrushStrokePart* part : parts) {
    delete part;
  }
}

void ImpBrush::BrushStroke::paint(const Point source, const Point target) {
  BrushSettings* settingsCopy = new BrushSettings(*settings);
  resolveSettings(settingsCopy, source);
  addPart(settingsCopy, source, target);
}

void ImpBrush::BrushStroke::replay() {
  begin();
  for (BrushStrokePart* part : parts) {
    Log::Debug << "Replaying: (" << part->target.x << ", " << part->target.y << ")" << Log::end;
    doPaint(part->settings, part->source, part->target);
  }
  end();
}

void ImpBrush::BrushStroke::resolveSettings(BrushSettings* settings, const Point source) const {
  if (settings->getColorMode() == ColorMode::FromSource) {
    unsigned char color[4];
    memcpy(color, doc->getOriginalPixel(source), 3);
    color[3] = settings->getOpacityAsChar();
    settings->setColor(color);
    settings->setColorMode(ColorMode::FixedColor);
  }
}

void ImpBrush::BrushStroke::addPart(BrushSettings* settings, const Point source, const Point target) {
  parts.push_back(new ImpBrush::BrushStrokePart(settings, source, target));
  doPaint(settings, source, target);
}

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
