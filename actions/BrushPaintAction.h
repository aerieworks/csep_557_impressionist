#pragma once
#include <vector>
#include "Action.h"
#include "../impBrush.h"
#include "../UndoableAction.h"

class BrushPaintAction : public UndoableAction {
public:
  BrushPaintAction(const unsigned char* current, const int width, const int height, ImpBrush::BrushStroke* stroke)
    : UndoableAction("Brush", current, width, height), stroke(stroke) {}

  ~BrushPaintAction();

  virtual bool doAction();
private:
  ImpBrush::BrushStroke* stroke;
};

