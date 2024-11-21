#ifndef GameObject_h
#define GameObject_h

#include <Arduino.h>

class GameObject
{
public:
  GameObject(int xCord, int yCord);

  int getXCord();
  int getYCord();

  void up();
  void down();
  void left();
  void right();

private:
  int _xCord;
  int _yCord;
};
#endif
