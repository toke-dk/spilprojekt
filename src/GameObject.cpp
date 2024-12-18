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

void GameObject::moveX()
{
  xCord = moveXCoord();

  _previousTime = _currentTime;
}

float GameObject::moveXCoord()
{
  _currentTime = millis() / 1000.0;          // Get the current time
  _deltaTime = _currentTime - _previousTime; // Calculate time difference

  return xCord + xVel * _deltaTime;
}
