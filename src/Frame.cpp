#include "Frame.h"
#include <list>
using namespace std;

Frame::Frame()
{
  byte initFrame[8] = {
      // 0b00000001,
      // 0b00000011,
      // 0b00000111,
      // 0b00001111,
      // 0b00011111,
      // 0b00111111,
      // 0b01111111,
      // 0b11111111,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
      0b00000000,
  };

  for (int i = 0; i < 8; i++)
  {
    _frame[i] = initFrame[i];
  }
}

byte *Frame::getFrame()
{
  return _frame;
}

list<GameObject> Frame::getObjects()
{
  return _gameObjects;
}

void Frame::addObject(GameObject object)
{
  _gameObjects.push_front(object);
}