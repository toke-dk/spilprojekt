#ifndef Frame_h
#define Frame_h

#include <Arduino.h>
#include "GameObject.h"

class Frame
{
public:
  Frame(size_t rows, size_t columns, size_t X_SEGMENTS, size_t Y_SEGMENTS);

  void addObject(GameObject &object);

  uint8_t *displayObjectsToArray();

  void set(float row, float col, bool value);
  int get(size_t row, size_t col);

  uint8_t *toCompactArray();

  void printGrid();

private:
  size_t _rows, _columns;
  bool _grid[16][16];
  GameObject *_gameObjects[100];
  size_t _amountOfObjects;

  size_t _X_SEGMENTS;
  size_t _Y_SEGMENTS;

  void _bounceIfEdge(GameObject *object);
};
#endif
