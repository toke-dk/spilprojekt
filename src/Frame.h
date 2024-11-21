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

  vector<GameObject *> getObjects();

  void addObject(GameObject &object);

  vector<uint8_t> displayObjectsToArray();

  void set(size_t row, size_t col, bool value);
  int get(size_t row, size_t col);

  vector<uint8_t> toCompactArray();

  void printGrid();

private:
  size_t _rows, _columns;
  vector<vector<bool>> _grid;
  vector<GameObject *> _gameObjects;
};
#endif
