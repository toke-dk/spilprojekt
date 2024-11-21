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
  float _currentTime = millis() / 1000.0;    // Get the current time
  _deltaTime = _currentTime - _previousTime; // Calculate time difference

  return xCord + xVel * _deltaTime;
}

float GameObject::moveYCoord()
{
  float _currentTime = millis() / 1000.0;    // Get the current time
  _deltaTime = _currentTime - _previousTime; // Calculate time difference

  return yCord + yVel * _deltaTime;
}

void GameObject::move()
{
  float _currentTime = millis() / 1000.0;
  _deltaTime = _currentTime - _previousTime; // Calculate time difference
  yCord += yVel * _deltaTime;
  xCord += xVel * _deltaTime;
  _previousTime = _currentTime;
}
