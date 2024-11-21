#include "Position.h"

Position::Position(int x, int y)
{
  _x = x;
  _y = y;
}

int Position::getX()
{
  return _x;
}

int Position::getY()
{
  return _y;
}

void Position::up()
{
  _y++;
}

void Position::down()
{
  _y--;
}

void Position::left()
{
  _x--;
}

void Position::right()
{
  _x++;
}
