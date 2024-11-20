#include "Position.h"
#include "GameObject.h"
#include "Frame.h"

int latchPin = 7;
int dataPin = 8;
int clockPin = 9;

const int rowCount = 8;
const int collumnCount = 8;

const byte rows[rowCount] = {0b11111110,0b11111101,0b11111011,0b11110111,0b11101111,0b11011111,0b10111111,0b01111111};

Frame frame = Frame();

Position ballPosition(2,2);
GameObject ball(ballPosition);

void setup() {
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // ball.right();
  // Serial.println(ball.pos().getX());
  // starter frame

  loadFrame();
  //delay(2);
}

void loadFrame() {
  
  for (int i = 0; i<collumnCount; i++) {
    digitalWrite(latchPin, LOW);
    
    // gå igennem rækkerne
    shiftOut(dataPin, clockPin, LSBFIRST, rows[i]);

    // tilføj din nuværende kolonne
    shiftOut(dataPin, clockPin, LSBFIRST, frame.getFrame()[i]);
    
    
    digitalWrite(latchPin, HIGH);    
    //delay(500);
  }
}
