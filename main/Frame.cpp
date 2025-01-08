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

  if (object.getType() == GameObject::STATIC)
  {
    _amountOfStaticObjects++;
  }

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
    _handleBarriers(_gameObjects[i], i);

    // if the object has a width
    for (size_t h = 0; h < _gameObjects[i]->height; h++)
    {
      for (size_t w = 0; w < _gameObjects[i]->width; w++)
      {
        set(_gameObjects[i]->xCord + w, _gameObjects[i]->yCord + h, _gameObjects[i]->color);
      }
    }
  }
}

void Frame::_handleBarriers(GameObject *object, int index)
{
  // check for bouncing objects
  if (object->getType() == GameObject::BOUNCING)
  {
    GameObject **staticObjects = getStaticObjects();

    for (size_t i = 0; i < _amountOfStaticObjects; i++)
    {
      if (object->xCord + object->width > staticObjects[i]->xCord &&
          object->xCord < staticObjects[i]->xCord + staticObjects[i]->width &&
          object->yCord + object->height > staticObjects[i]->yCord &&
          object->yCord < staticObjects[i]->yCord + staticObjects[i]->height)
      {
        float closestXEdge = min(
            staticObjects[i]->xCord + staticObjects[i]->width - object->xCord - object->width,
            object->xCord - staticObjects[i]->xCord);

        float closestYEdge = min(
            staticObjects[i]->yCord + staticObjects[i]->height - object->yCord - object->height,
            object->yCord - staticObjects[i]->yCord);

        if (min(closestXEdge, closestYEdge) == closestXEdge)
        {
          object->xVel *= -1;
        }
        else
        {
          object->yVel *= -1;
        }

        // Serial.print("Collision ");
      }
    }

    delete[] staticObjects;

    // Checks if there is collision with right border then update score
    if (object->xCord > _columns - 1)
    {
      /// resets the ball
      resetObjectPosition(object);
      p1Score += 1;
    }

    // Checks if there is collision with left border then update score
    if (object->xCord < 0)
    {
      resetObjectPosition(object);
      p2Score += 1;
    }

    // If someone reaches score 10 reset score
    if (p1Score >= 10 || p2Score >= 10)
    {
      p1Score = 0;
      p2Score = 0;
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
  else if (object->getType() == GameObject::STATIC)
  {
    // Checks if there is collision with right border
    if (object->xCord + object->width > _columns)
    {
      object->xCord = _columns - object->width;
    }
    // Check if behind left border
    if (object->xCord < 0)
    {
      object->xCord = 0;
    }
    // Checks if there is collision with top borders
    if (object->yCord + object->height > _rows)
    {
      object->yCord = _rows - object->height;
    }
    // Check if below bottom border
    if (object->yCord < 0)
    {
      object->yCord = 0;
    }
  }
}

void Frame::resetObjectPosition(GameObject *object)
{
  object->xCord = 7;
  object->yCord = 7;
}

// Set a specific cell
void Frame::set(float col, float row, GameObject::Colors color)
{
  int colortoAdd = 1;
  switch (color)
  {
  case GameObject::RED:
    colortoAdd = 1;
    break;
  case GameObject::GREEN:
    colortoAdd = 2;
    break;
  case GameObject::YELLOW:
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

GameObject **Frame::getStaticObjects()
{
  // Dynamically allocate memory based on the number of bouncing objects
  GameObject **bouncingObjects = new GameObject *[_amountOfObjects];

  int index = 0;
  for (size_t i = 0; i < _amountOfObjects; i++)
  {
    if (_gameObjects[i]->getType() == GameObject::STATIC)
    {
      bouncingObjects[index] = _gameObjects[i];
      index++;
    }
  }

  // Optionally resize if needed (not necessary with this approach)
  return bouncingObjects;
}

void removeElement(int arr[], int &size, int index)
{
  for (int i = index; i < size - 1; ++i)
  {
    arr[i] = arr[i + 1];
  }
  --size; // Reduce the size
}