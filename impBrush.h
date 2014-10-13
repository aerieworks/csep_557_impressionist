#ifndef IMPBRUSH_H
#define IMPBRUSH_H

#define PI 3.1415926535897932384626433832795

//
// ImpBrush.h
//
// The header file of virtual brush. All the other brushes inherit from it.
//

#include <stdlib.h>
#include <vector>
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

  struct BrushStrokePart {
    BrushStrokePart(BrushSettings* settings, const Point source, const Point target)
      : settings(settings), source(source), target(target) { }

    ~BrushStrokePart() {
      delete settings;
    }

    BrushSettings* settings;
    const Point source;
    const Point target;
  };
public:
  class BrushStroke {
  public: 
    BrushStroke(ImpressionistDoc* const doc, const BrushSettings* settings) : doc(doc), settings(settings) {}
    ~BrushStroke();

    virtual void begin() = 0;
    virtual void paint(const Point source, const Point target);
    virtual void end() {}
    virtual void replay();
  protected:
    void addPart(BrushSettings* settings, const Point source, const Point target);
    virtual void resolveSettings(BrushSettings* settings, const Point source) const;
    virtual void doPaint(const BrushSettings* settings, const Point source, const Point target) = 0;

    const BrushSettings* settings;
    ImpressionistDoc* const doc;
  private:
    std::vector<BrushStrokePart*> parts;
  };

  virtual BrushStroke* createStroke() = 0;

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

