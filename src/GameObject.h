#ifndef GameObject_h
#define GameObject_h

#include <Arduino.h>

class GameObject
{
public:
  GameObject(float xCord, float yCord);

  float xVel;
  float yVel;

  float getXCord();
  float getYCord();

  void up();
  void down();
  void left();
  void right();

  void move();

private:
  float _xCord;
  float _yCord;
};
#endif
