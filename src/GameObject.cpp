#include "GameObject.h"
float previousTime = 0; // Store the last frame time
float currentTime = 0;  // Store the current frame time
float deltaTime = 0;    // Store the time difference between frames

GameObject::GameObject(float xCord, float yCord)
{
  _xCord = xCord;
  _yCord = yCord;
}

float GameObject::getXCord() { return _xCord; };

float GameObject::getYCord() { return _yCord; };

void GameObject::up()
{
  _yCord++;
}

void GameObject::down()
{
  _yCord--;
}

void GameObject::left()
{
  _xCord--;
}

void GameObject::right()
{
  _xCord++;
}

void GameObject::move()
{
  currentTime = millis() / 1000.0;        // Get the current time
  deltaTime = currentTime - previousTime; // Calculate time difference

  _xCord += (xVel * deltaTime);

  previousTime = currentTime;
}
