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

// TODO: the ball should be able to have decimal coordinates
GameObject ball(0, 0);
Frame frame;

void setup()
{
    frame.addObject(ball);
    Serial.begin(115200);
    Serial.print(ball.getXCord());
    Serial.print("Start");
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    ball.xVel = 1;
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
    frame.getFrame()[object.getYCord()] |= (1 << (object.getXCord()));

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

    ball.move();
    delay(1000);
    // Serial.print(object.getXCord());
}
