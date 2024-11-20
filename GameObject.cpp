#include "Position.h"
#include "GameObject.h"

GameObject::GameObject(Position pos) : _pos(pos) {
}

int GameObject::getPosX() {
  return _pos.getX();
}
