#ifndef GameObject_h
#define GameObject_h

#include <Arduino.h>

class GameObject
{
public:
  enum ObjectType
  {
    STATIC,
    BOUNCING
  };
  enum Colors
  {
    RED,
    GREEN,
    YELLOW
  };

  GameObject(float xCord, float yCord, enum GameObject::ObjectType type, GameObject::Colors color);

  GameObject::ObjectType getType();

  GameObject::Colors color;

  float xVel;
  float yVel;

  float xCord;
  float yCord;

  float width = 1;
  float height = 1;

  void up();
  void down();
  void left();
  void right();

  float moveXCoord();

  float moveYCoord();

  void move();

  bool isColliding(GameObject &other);

private:
  float _previousTime = 0; // Store the last frame time
  float _deltaTime = 0;    // Store the time difference between frames
  float _currentTime = 0;  // Store the current time
  void _moveY();
  void _moveX();
  GameObject::ObjectType _type;
};
#endif
