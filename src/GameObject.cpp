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
}
