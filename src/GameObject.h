#ifndef GameObject_h
#define GameObject_h

#include <Arduino.h>

class GameObject
{
public:
  GameObject(int xCord, int yCord);

  int xVel;
  int yVel;

  int getXCord();
  int getYCord();

  void up();
  void down();
  void left();
  void right();

  void move();

private:
  int _xCord;
  int _yCord;
  
};
#endif
