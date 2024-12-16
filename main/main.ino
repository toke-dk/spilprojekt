#include "GameObject.h"
#include "Frame.h"

#define latchPin 10
#define dataPin 11
#define clockPin 13

const int rowCount = 8;
const int collumnCount = 8;

const byte rows[rowCount] = {0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b11101111, 0b11011111, 0b10111111, 0b01111111};

byte frameTest[8] = { 0b00000001,
                  0b00000011,0b00000111,0b00001111,0b00011111,0b00111111,0b01111111,0b11111111};


// TODO: the ball should be able to have decimal coordinates
GameObject ball(3, 7);
// GameObject ball2(1, 2);
// frame.addObject(ball2);

// ball2.xVel = 10;
// ball2.yVel = 8;
Frame frame(8, 8);

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    delay(500);
    frame.addObject(ball);

    ball.xVel = 5;
    ball.yVel = -5;
}

void loop()
{
    // ball.right();
    // Serial.println(ball.pos().getX());
    // starter frame

    loadFrame();
    // delay(2);
}

void loadFrame()
{
    uint8_t *bitDisplay = frame.displayObjectsToArray();

    for (byte i = 0; i < collumnCount; i++)
    {
        digitalWrite(latchPin, LOW);

        // gå igennem rækkerne
        shiftOut(dataPin, clockPin, MSBFIRST, rows[i]);

        // tilføj din nuværende kolonne
        shiftOut(dataPin, clockPin, LSBFIRST, bitDisplay[i]);

        digitalWrite(latchPin, HIGH);
        // delay(500);
    }
    // reset the bit to clear memory
    delete[] bitDisplay;

    delay(10);
    // Serial.print(object.getXCord());
}
