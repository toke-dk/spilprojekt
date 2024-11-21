#include "Frame.h"
#include <list>
using namespace std;

Frame::Frame(size_t rows, size_t columns) : _grid(rows, vector<bool>(columns, false))
{
}

vector<GameObject> Frame::getObjects()
{
  return _gameObjects;
}

void Frame::addObject(GameObject object)
{
  _gameObjects.push_back(object);
}

vector<uint8_t> Frame::displayObjectsToArray()
{

  for (size_t i = 0; i < _gameObjects.size(); i++)
  {
    set(_gameObjects[i].getYCord(), _gameObjects[i].getXCord(), true);
  }
  return toCompactArray();
}

// Set a specific cell
void Frame::set(size_t row, size_t col, bool value)
{
  _grid[row][col] = value;
}

// Get a specific cell
int Frame::get(size_t row, size_t col)
{
  return _grid[row][col];
}

// Convert to a compact bit-representation
vector<uint8_t> Frame::toCompactArray()
{
  size_t rows = _grid.size();
  size_t cols = _grid[0].size();
  std::vector<uint8_t> compact(rows, 0);

  for (size_t i = 0; i < rows; ++i)
  {
    for (size_t j = 0; j < cols; ++j)
    {
      if (_grid[i][j])
      {
        compact[i] |= (1 << j);
      }
    }
  }
  return compact;
}

void Frame::printGrid()
{
  for (const auto &row : _grid)
  {
    for (bool cell : row)
    {
      Serial.print(cell ? "1" : "0");
    }
    Serial.println("f");
  }
}