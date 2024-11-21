#include "Position.h"
#include "GameObject.h"

GameObject::GameObject(Position pos) : _pos(pos)
{
}

Position GameObject::pos()
{
  return _pos;
}

void GameObject::up()
{
  _pos.up();
}

void GameObject::down()
{
  _pos.down();
}

void GameObject::left()
{
  _pos.left();
}

void GameObject::right()
{
  _pos.right();
}
