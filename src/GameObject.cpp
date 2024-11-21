#include "GameObject.h"

GameObject::GameObject(int xCord, int yCord)
{
  _xCord = xCord;
  _yCord = yCord;
}

int GameObject::getXCord() { return _xCord; };

int GameObject::getYCord() { return _yCord; };

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
  Serial.println(_xCord);
}
