#ifndef GameObject_h
#define GameObject_h

#include <Arduino.h>
#include "Position.h"

class GameObject
{
public:
  GameObject(Position pos);
  Position pos();

  void up();
  void down();
  void left();
  void right();

private:
  Position _pos;
};
#endif
