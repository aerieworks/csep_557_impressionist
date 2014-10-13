#ifndef ACTION_H
#define ACTION_H

class Action {
public:
  Action() {}

  virtual bool doAction() = 0;
};
#endif
