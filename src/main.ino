#include "Position.h"
#include "GameObject.h"
#include "Frame.h"
#include <list>
#include <vector>
using namespace std;

#define latchPin 10
#define dataPin 11
#define clockPin 13

const int rowCount = 8;
const int collumnCount = 8;

const byte rows[rowCount] = {0b11111110, 0b11111101, 0b11111011, 0b11110111, 0b11101111, 0b11011111, 0b10111111, 0b01111111};

Position ballPosition(1, 2);
GameObject ball(ballPosition);
Frame frame;

void setup()
{
    frame.addObject(ball);
    Serial.begin(115200);
    Serial.print("Start");
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
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
    GameObject object = frame.getObjects().front();
    frame.getFrame()[object.pos().getY()] |= (1 << object.pos().getX());

    for (byte i = 0; i < collumnCount; i++)
    {
        digitalWrite(latchPin, LOW);

        // gå igennem rækkerne
        shiftOut(dataPin, clockPin, MSBFIRST, 8 - i);

        // tilføj din nuværende kolonne
        shiftOut(dataPin, clockPin, LSBFIRST, frame.getFrame()[i]);

        digitalWrite(latchPin, HIGH);
        // delay(500);
    }
}
