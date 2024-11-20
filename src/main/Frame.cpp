#include "Frame.h"

Frame::Frame() {
  byte initFrame[8] = {
    0b00000001,
    0b00000011,
    0b00000111,
    0b00001111,
    0b00011111,
    0b00111111,
    0b01111111,
    0b11111111,
  };

  for (int i = 0; i < 8; i++) {
    _frame[i] = initFrame[i];
  }
}

byte* Frame::getFrame() {
  return _frame;
}
