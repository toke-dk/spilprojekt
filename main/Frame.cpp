#include "Frame.h"
using namespace std;

Frame::Frame(size_t X_SEGMENTS, size_t Y_SEGMENTS) : _rows(Y_SEGMENTS * 8), _columns(X_SEGMENTS * 8), _X_SEGMENTS(X_SEGMENTS), _Y_SEGMENTS(Y_SEGMENTS)
{
  // Allocate memory for rows
  grid = new int *[16];
  for (size_t i = 0; i < 16; ++i)
  {
    // Allocate memory for columns in each row
    grid[i] = new int[16];

    // Initialize all elements to 0
    for (size_t j = 0; j < 16; ++j)
    {
      grid[i][j] = 0;
    }
  }
}

Frame::~Frame()
{
  for (size_t i = 0; i < 16; ++i)
  {
    delete[] grid[i]; // Free each row
  }
  delete[] grid; // Free the row pointers
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

void Frame::placeObjectsToGrid()
{

  // reset the old grid to draw a new
  for (size_t i = 0; i < _rows; i++)
  {
    for (size_t j = 0; j < _columns; j++)
    {
      grid[i][j] = 0; // Set each element to 0
    }
  };

  // check if bounce for each object
  for (size_t i = 0; i < _amountOfObjects; i++)
  {

    _gameObjects[i]->move();

    // correction of moving gameobjects
    _bounceIfEdge(_gameObjects[i]);

    // if the object has a width
    for (size_t h = 0; h < _gameObjects[i]->height; h++)
    {
      for (size_t w = 0; w < _gameObjects[i]->width; w++)
      {
        set(_gameObjects[i]->xCord + w, _gameObjects[i]->yCord + h, RED);
      }
    }
  }
}

void Frame::_bounceIfEdge(GameObject *object)
{
  // Checks if there is collision with right border
  if (object->xCord > _columns - 1)
  {
    float correctionAmountX = 2 * (_columns - 1) - object->xCord;
    object->xCord = correctionAmountX;
    object->xVel *= -1;
  }
  // Check if behind left border
  if (object->xCord < 0)
  {
    object->xCord = -object->xCord;
    object->xVel *= -1;
  }

  // Checks if there is collision with top borders
  if (object->yCord > _rows - 1)
  {
    float correctionAmountY = 2 * (_rows - 1) - object->yCord;
    object->yCord = correctionAmountY;
    object->yVel *= -1;
  }
  // Check if below bottom border
  if (object->yCord < 0)
  {
    object->yCord = -object->yCord;
    object->yVel *= -1;
  }
}

// Set a specific cell
void Frame::set(float col, float row, enum Colors color)
{
  int colortoAdd = 1;
  switch (color)
  {
  case RED:
    colortoAdd = 1;
    break;
  case GREEN:
    colortoAdd = 2;
    break;
  case YELLOW:
    colortoAdd = 3;
    break;

  default:
    break;
  }
  // IDK why i should _columns - 1but it works
  grid[round(row)][(_columns - 1) - round(col)] = colortoAdd;
}

// Get a specific cell
int Frame::get(size_t row, size_t col)
{
  return grid[row][col];
}
