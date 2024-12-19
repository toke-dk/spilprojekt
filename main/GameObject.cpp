#include "GameObject.h"

GameObject::GameObject(float xCord, float yCord, GameObject::ObjectType type) : xCord(xCord), yCord(yCord), _type(type)
{
}

void GameObject::up()
{
  yCord--;
}

void GameObject::down()
{
  yCord++;
}

void GameObject::left()
{
  xCord--;
}

void GameObject::right()
{
  xCord++;
}

float GameObject::moveXCoord()
{
  return xCord + xVel * _deltaTime;
}

float GameObject::moveYCoord()
{
  return yCord + yVel * _deltaTime;
}

void GameObject::move()
{
  _currentTime = millis() / 1000.0;

  _deltaTime = _currentTime - _previousTime; // Calculate time difference

  yCord += yVel * _deltaTime;
  xCord += xVel * _deltaTime;

  _previousTime = _currentTime;

  // Serial.println("Move");
  // Serial.println(yCord);
  // TODO the time and maybe x and y coordinates need more digits (long)
}

GameObject::ObjectType GameObject::getType()
{
  return _type;
};

bool GameObject::isColliding(GameObject &other)
{
  return xCord < other.xCord + other.width &&
         xCord + width > other.xCord &&
         yCord < other.yCord + other.height &&
         yCord + height > other.yCord;
}
