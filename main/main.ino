#include "GameObject.h"
#include "Frame.h"

#define latchPin 10
#define dataPin 11
#define clockPin 13
#define X_SEGMENTS 1
#define Y_SEGMENTS 1
#define NUM_SEGMENTS (X_SEGMENTS * Y_SEGMENTS)

const int rowCount = 16;
const int collumnCount = 16;

const word rows[rowCount] = {
    0b1111111111111110,
    0b1111111111111101,
    0b1111111111111011,
    0b1111111111110111,
    0b1111111111101111,
    0b1111111111011111,
    0b1111111110111111,
    0b1111111101111111,
    0b1111111011111111,
    0b1111110111111111,
    0b1111101111111111,
    0b1111011111111111,
    0b1110111111111111,
    0b1101111111111111,
    0b1011111111111111,
    0b0111111111111111,
};

// to farver derfor to slags 16*16
word frameTest[rowCount * 2] = {
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b1000000000000000,

    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
    0b0000000000000000,
};

// TODO: the ball should be able to have decimal coordinates
GameObject ball(1, 5);
// GameObject ball2(1, 2);
// frame.addObject(ball2);

// ball2.xVel = 10;
// ball2.yVel = 8;
Frame frame(X_SEGMENTS, Y_SEGMENTS);

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    delay(500);
    frame.addObject(ball);

    ball.xVel = 20;
    ball.yVel = 15;
}

void loop()
{
    // ball.right();
    // Serial.println(ball.pos().getX());
    // starter frame

    loadFrame();
    // delay(2);
}

void shiftOut16(uint16_t _dataPin, uint16_t _clockPin, uint16_t _bitOrder, uint16_t _val)
{
    uint16_t i;

    for (i = 0; i < 16; i++)
    {
        if (_bitOrder == LSBFIRST)
            digitalWrite(_dataPin, !!(_val & (1 << i)));
        else
            digitalWrite(_dataPin, !!(_val & (1 << (15 - i))));

        digitalWrite(_clockPin, HIGH);
        digitalWrite(_clockPin, LOW);
    }
}

void loadFrame()
{
    uint8_t *bitDisplay = frame.displayObjectsToArray();

    for (word i = 0; i < 8; i++)
    {
        digitalWrite(latchPin, LOW);

        // gå igennem rækkerne
        shiftOut(dataPin, clockPin, MSBFIRST, 8 - i);

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
