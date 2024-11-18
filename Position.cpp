#ifndef Position_h
#define Position_h
#include "Arduino.h"

class Position {
  public:
    Position(int x, int y);
  private:
    int _x;
    int _y;
};

#endif
