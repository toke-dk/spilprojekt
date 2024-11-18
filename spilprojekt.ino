int latchPin = 7;
int dataPin = 8;
int clockPin = 9;

const byte rows[8] = {0b11111110,0b11111101,0b11111011,0b11110111,0b11101111,0b11011111,0b10111111,0b01c111111};
const byte frame[8] = {0b00000001,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000,0b00000000};

void setup() {
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
}

void loop() {
  // starter frame
  loadFrame();
  
}

void loadFrame() {
  
  for (int i = 0; i<8, i++;) {
    digitalWrite(latchPin, LOW);
    
    // gå igennem rækkerne
    shiftOut(dataPin, clockPin, LSBFIRST, rows[i]);

    // tilføj din nuværende række
    shiftOut(dataPin, clockPin, LSBFIRST, frame[i]);
    
    
    digitalWrite(latchPin, HIGH);
  }
}
