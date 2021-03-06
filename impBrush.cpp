//
// impBrush.cpp
//
// The implementation of virtual brush. All the other brushes inherit from it.
//

#include <random>
#include "impressionistDoc.h"
#include "impressionistUI.h"
#include "impBrush.h"
#include "Log.h"

// Static class member initializations
int			ImpBrush::c_nBrushCount = 0;
ImpBrush**	ImpBrush::c_pBrushes = NULL;

ImpBrush::BrushStroke::~BrushStroke() {
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

double ImpBrush::BrushStroke::getRandomOffset(const double min, const double max) const {
  const double offsetPercentage = (double)rand() / (double)RAND_MAX;
  return min + (max - min) * offsetPercentage;
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
