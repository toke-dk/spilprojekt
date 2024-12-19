#include "GameObject.h"
#include "Frame.h"

#define latchPin 10
#define dataPin 11
#define clockPin 13
#define X_SEGMENTS 2
#define Y_SEGMENTS 2
#define SEGMENTS_TOTAL (X_SEGMENTS * Y_SEGMENTS)

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

int array[16][16] = {
    {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 3, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 3, 2, 1, 1, 1, 1, 2, 3, 0, 0, 0, 0},
    {0, 0, 0, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0},
    {0, 0, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0},
    {0, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0},
    {3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3},
    {0, 3, 2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0},
    {0, 0, 3, 2, 1, 0, 0, 0, 0, 0, 0, 1, 2, 3, 0, 0},
    {0, 0, 0, 3, 2, 1, 0, 0, 0, 0, 1, 2, 3, 0, 0, 0},
    {0, 0, 0, 0, 3, 2, 1, 1, 1, 1, 2, 3, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 3, 2, 2, 2, 2, 3, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 3, 3, 3, 3, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 3, 3, 3, 0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

// TODO: the ball should be able to have decimal coordinates
GameObject ball(0, 6, GameObject::BOUNCING);
GameObject playerOne(5, 5, GameObject::STATIC);
// GameObject ball2(1, 2);
// frame.addObject(ball2);

// ball2.xVel = 10;
// ball2.yVel = 8;
Frame frame(X_SEGMENTS, Y_SEGMENTS);

void setup()
{
    Serial.begin(9600);
    Serial.println("Start");
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    // delay(500);
    frame.addObject(ball);
    frame.addObject(playerOne);

    ball.xVel = 30;
    ball.yVel = 26;

    playerOne.height = 3;
    playerOne.width = 7;
}

void loop()
{
    if (Serial.available() > 0)
    {
        char receivedChar = Serial.read(); // Read one character
        Serial.print("You pressed: ");
        Serial.println(receivedChar); // Echo back the character
        if (receivedChar == 'w')
        {
            playerOne.up();
        }
        if (receivedChar == 'a')
        {
            playerOne.left();
        }
        else if (receivedChar == 's')
        {
            playerOne.down();
        }
        else if (receivedChar == 'd')
        {
            playerOne.right();
        }
    }
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
    frame.placeObjectsToGrid();
    // Serial.println(frame.grid[0][6]);
    for (int currentRow = 0; currentRow < 16; currentRow++)
    {
        uint16_t Val = rows[currentRow]; // Repræsenterer første bitmønster
        uint16_t redPixels = 0;          // Repræsenterer første bitmønster
        uint16_t greenPixels = 0;        // Repræsenterer andet bitmønster
        // Behandl den aktuelle række i arrayet
        for (int i = 0; i < 16; i++)
        {
            switch (frame.grid[currentRow][i])
            {
            case 1: // 1 i Val2 og 0 i Val3
                redPixels |= (1 << i);
                greenPixels |= (0 << i);
                break;
            case 2: // 0 i Val2 og 1 i Val3
                redPixels |= (0 << i);
                greenPixels |= (1 << i);
                break;
            case 3: // 1 i både Val2 og Val3
                redPixels |= (1 << i);
                greenPixels |= (1 << i);
                break;
            case 0: // Sæt bit i Val
                redPixels |= (0 << i);
                greenPixels |= (0 << i);
                break;
            default:
                break;
            }
        }

        digitalWrite(latchPin, LOW);                          // Forbered latch
        shiftOut16(dataPin, clockPin, LSBFIRST, Val);         // Send Val
        shiftOut16(dataPin, clockPin, MSBFIRST, redPixels);   // Send Val2
        shiftOut16(dataPin, clockPin, MSBFIRST, greenPixels); // Send Val3
        digitalWrite(latchPin, HIGH);                         // Aktivér latch for at opdatere output

        // Gå til næste række i arrayet    // delay(500);
    }
}