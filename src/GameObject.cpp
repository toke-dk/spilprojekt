#include "GameObject.h"

GameObject::GameObject(float xCord, float yCord) : xCord(xCord), yCord(yCord)
{
}

void GameObject::up()
{
  yCord++;
}

void GameObject::down()
{
  yCord--;
}

void GameObject::left()
{
  xCord--;
}

void GameObject::right()
{
  xCord++;
}

void GameObject::_moveX()
{
  xCord = moveXCoord();
}

float GameObject::moveXCoord()
{
  _currentTime = millis() / 1000.0;          // Get the current time
  _deltaTime = _currentTime - _previousTime; // Calculate time difference

  return xCord + xVel * _deltaTime;
}

void GameObject::_moveY()
{
  yCord = moveYCoord();
}

float GameObject::moveYCoord()
{
  _currentTime = millis() / 1000.0;          // Get the current time
  _deltaTime = _currentTime - _previousTime; // Calculate time difference

  return yCord + yVel * _deltaTime;
}

void GameObject::move()
{
  _moveX();
  _moveY();
  _previousTime = _currentTime;
}
