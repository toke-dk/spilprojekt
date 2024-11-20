#include "Position.h"
#include "GameObject.h"

int latchPin = 7;
int dataPin = 8;
int clockPin = 9;

const byte rows[8] = {0b11111110,0b11111101,0b11111011,0b11110111,0b11101111,0b11011111,0b10111111,0b01111111};

byte frame[8] = { 0b00000001,
                  0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111};

Position ballPosition(2,2);
GameObject ball(ballPosition);

void setup() {
  Serial.print(ball.getPosX());
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // starter frame
  loadFrame();
  //delay(2);
}

void loadFrame() {
  
  for (int i = 0; i<8; i++) {
    digitalWrite(latchPin, LOW);
    
    // gå igennem rækkerne
    shiftOut(dataPin, clockPin, LSBFIRST, rows[i]);
    //Serial.println("done");

    // tilføj din nuværende række
    shiftOut(dataPin, clockPin, LSBFIRST, frame[i]);
    
    
    digitalWrite(latchPin, HIGH);
    delay(500);
  }
}
