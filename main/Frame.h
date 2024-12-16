#ifndef Frame_h
#define Frame_h

#include <Arduino.h>
#include "GameObject.h"
#include <list>
#include <vector>
using namespace std;

class Frame
{
public:
  Frame(size_t rows, size_t columns);

  void addObject(GameObject &object);

  uint8_t *displayObjectsToArray();

  void set(float row, float col, bool value);
  int get(size_t row, size_t col);

  uint8_t *toCompactArray();

  void printGrid();

private:
  size_t _rows, _columns;
  bool _grid[8][8];
  GameObject *_gameObjects[100];
  size_t _amountOfObjects;

  void _bounceIfEdge(GameObject *object);
};
#endif
