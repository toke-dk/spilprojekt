#ifndef Frame_h
#define Frame_h

#include <Arduino.h>
#include "GameObject.h"
#include <list>
using namespace std;

class Frame
{
public:
  Frame();

  byte *getFrame();
  list<GameObject> getObjects();
  void addObject(GameObject object);

private:
  byte _frame[8];
  list<GameObject> _gameObjects;
};
#endif
