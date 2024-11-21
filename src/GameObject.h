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

  void move();

private:
  float _previousTime = 0; // Store the last frame time
  float _currentTime = 0;  // Store the current frame time
  float _deltaTime = 0;    // Store the time difference between frames
};
#endif
