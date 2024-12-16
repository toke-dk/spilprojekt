#include "Frame.h"
#include <list>
#include <cmath>
using namespace std;

Frame::Frame(size_t rows, size_t columns) : _rows(rows), _columns(columns), _grid()
{
}

void Frame::addObject(GameObject &object)
{
  _amountOfObjects++;

  // Point the last element to the new object
  _gameObjects[_amountOfObjects - 1] = &object;
  // Serial.println(_gameObjects[0]->xCord);

  Serial.print("x:cord");
  Serial.println(_gameObjects[1]->xCord);
  Serial.print("y:cord");
  Serial.println(_gameObjects[1]->yCord);
}

uint8_t *Frame::displayObjectsToArray()
{

  // reset the old grid to draw a new
  for (size_t i = 0; i < _rows; i++)
  {
    for (size_t j = 0; j < _columns; j++)
    {
      _grid[i][j] = 0; // Set each element to 0
    }
  };

  // check if bounce for each object
  for (size_t i = 0; i < _amountOfObjects; i++)
  {

    // after checking for bounce it should move the object
    _bounceIfEdge(_gameObjects[i]);

    _gameObjects[i]->move();

    set(_gameObjects[i]->yCord, _gameObjects[i]->xCord, true);
  }
  return toCompactArray();
}

// Convert to a compact bit-representation
uint8_t *Frame::toCompactArray()
{
  size_t rows = sizeof(_grid) / sizeof(_grid[0]);       // Total size / size of one row
  size_t cols = sizeof(_grid[0]) / sizeof(_grid[0][0]); // Size of one row / size of one element

  // Dynamically allocate an array of uint8_t
  uint8_t *compact = new uint8_t[rows]();

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
  return compact; // Caller must free the memory
}

void Frame::_bounceIfEdge(GameObject *object)
{
  // Checks if there is collision with vertical borders
  if (object->moveXCoord() > _rows - 1 || object->moveXCoord() < 0)
  {
    object->xVel *= -1;
  }
  // Checks if there is collision with horizontal borders
  if (object->moveYCoord() > _columns - 1 || object->moveYCoord() < 0)
  {
    object->yVel *= -1;
  }
}

// Set a specific cell
void Frame::set(float row, float col, bool value)
{
  _grid[round(row)][round(col)] = value;
}

// Get a specific cell
int Frame::get(size_t row, size_t col)
{
  return _grid[row][col];
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