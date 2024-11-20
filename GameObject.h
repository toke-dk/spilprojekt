#ifndef GameObject_h
#define GameObject_h

#include <Arduino.h>
#include "Position.h"

class GameObject {
  public:
    GameObject(Position pos);
    int getPosX();
    
  private:
    Position _pos;
    
};
#endif
