#include "Position.h"
#include "GameObject.h"

GameObject::GameObject(Position pos) : _pos(pos) {
}

Position GameObject::pos() {
  return _pos;
}

void GameObject::moveUp() {
  _pos.up();
}
