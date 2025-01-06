#ifndef Frame_h
#define Frame_h

#include <Arduino.h>
#include "GameObject.h"

class Frame
{
public:
  Frame(size_t X_SEGMENTS, size_t Y_SEGMENTS);

  void addObject(GameObject &object);

  void placeObjectsToGrid();

  void set(float row, float col, GameObject::Colors color);
  int get(size_t row, size_t col);

  uint8_t *toCompactArray();

  void printGrid();

  int **grid;

  GameObject **getStaticObjects();

  ~Frame(); // Declare the destructor

private:
  size_t _rows, _columns;
  GameObject *_gameObjects[100];
  size_t _amountOfObjects;
  size_t _amountOfStaticObjects;

  size_t _X_SEGMENTS;
  size_t _Y_SEGMENTS;

  void _handleBarriers(GameObject *object);
};
#endif
