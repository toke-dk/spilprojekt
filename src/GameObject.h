#ifndef GameObject_h
#define GameObject_h

#include <Arduino.h>

class GameObject
{
public:
  GameObject(float xCord, float yCord);

  float xVel;
  float yVel;

  float xCord;
  float yCord;

  void up();
  void down();
  void left();
  void right();

  float moveXCoord();

  float moveYCoord();

  void move();

private:
  float _previousTime = 0; // Store the last frame time
  float _deltaTime = 0;    // Store the time difference between frames
  void _moveY();
  void _moveX();
};
#endif
