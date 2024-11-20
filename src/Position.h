#ifndef Button_h
#define Button_h

#include <Arduino.h>

class Position
{
public:
  Position(int x, int y);

  int getX();
  int getY();

  void up();
  void down();
  void left();
  void right();

private:
  int _x;
  int _y;
};
#endif
