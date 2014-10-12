#ifndef IMPBRUSH_H
#define IMPBRUSH_H

#define PI 3.1415926535897932384626433832795

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>
#include "Area.h"
#include "viewModels/BrushSettings.h"

// Each brush type has an associated constant.
enum {
  BRUSH_POINTS = 0,
  BRUSH_LINES,
  BRUSH_CIRCLES,
  BRUSH_SCATTERED_POINTS,
  BRUSH_SCATTERED_LINES,
  BRUSH_SCATTERED_CIRCLES,
  NUM_BRUSH_TYPE // Make sure this stays at the end!
};


class ImpressionistDoc; // Pre-declaring class

class Point {
public:
  Point() {};
  Point(int xx, int yy) { x = xx; y = yy; };

  int x, y;
};

class ImpBrush {
protected:
  ImpBrush(ImpressionistDoc* pDoc = NULL, char* name = NULL);

public:
  // The implementation of your brush should realize these virtual functions
  virtual Area* brushBegin(const Point source, const Point target) = 0;
  virtual Area* brushMove(const Point source, const Point target) = 0;
  virtual Area* brushEnd(const Point source, const Point target) = 0;

  // according to the source image and the position, determine the draw color
  void setColor(const Point source);

  // get Doc to communicate with it
  ImpressionistDoc* getDocument(void);

  // Return the name of the brush (not used in this version).
  char* getBrushName(void);

  BrushSettings* getSettings();

  static int			c_nBrushCount;	// How many brushes we have,
  static ImpBrush**	c_pBrushes;		// and what they are.

private:
  ImpressionistDoc*	m_pDoc;

  // Brush's name (not used in this version).
  char*				m_pBrushName;
  BrushSettings		m_settings;
};

#endif

