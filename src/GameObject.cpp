#include "GameObject.h"

GameObject::GameObject(float xCord, float yCord)
{
  _xCord = xCord;
  _yCord = yCord;
}

float GameObject::getXCord() { return _xCord; };

float GameObject::getYCord() { return _yCord; };

void GameObject::up()
{
  _yCord++;
}

void GameObject::down()
{
  _yCord--;
}

void GameObject::left()
{
  _xCord--;
}

void GameObject::right()
{
  _xCord++;
}

void GameObject::move()
{
  _xCord += xVel;
}
