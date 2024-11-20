#ifndef Frame_h
#define Frame_h

#include <Arduino.h>


class Frame {
  public:
    Frame();

    byte* getFrame();
    
  private:
    byte _frame[8];
};
#endif
