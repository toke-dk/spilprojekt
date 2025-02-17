#include "GameObject.h"
#include "Frame.h"

#define latchPin 10 // Gul
#define dataPin 11  // Grøn
#define clockPin 13 // Lyserød

#define latchPinScore 5 // Gul
#define dataPinScore 4  // Grøn
#define clockPinScore 3 // Lyserød

#define X_SEGMENTS 2
#define Y_SEGMENTS 2
#define PLAYER_HEIGHT 5
#define SEGMENTS_TOTAL (X_SEGMENTS * Y_SEGMENTS)

const int rowCount = 16;
const int collumnCount = 16;
const int p1Up = 7;
const int p1Down = 6;
const int p2Up = 8;
const int p2Down = 9;

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

// TODO: the ball should be able to have decimal coordinates
GameObject ball(0, 0, GameObject::BOUNCING, GameObject::RED);
GameObject playerLeft(0, rowCount - PLAYER_HEIGHT, GameObject::STATIC, GameObject::GREEN);
GameObject playerRight(collumnCount - 1, rowCount - PLAYER_HEIGHT, GameObject::STATIC, GameObject::GREEN);

// GameObject ball2(1, 2);
// frame.addObject(ball2);

// ball2.xVel = 10;
// ball2.yVel = 8;
Frame frame(X_SEGMENTS, Y_SEGMENTS);

int p1OldScore = 0;
int p2OldScore = 0;

void setup()
{
    Serial.begin(9600);
    Serial.println("Start");

    // Frame pins
    pinMode(latchPin, OUTPUT);
    pinMode(dataPin, OUTPUT);
    pinMode(clockPin, OUTPUT);

    // Score pins
    pinMode(latchPinScore, OUTPUT);
    pinMode(dataPinScore, OUTPUT);
    pinMode(clockPinScore, OUTPUT);

    pinMode(p1Up, INPUT);
    pinMode(p1Down, INPUT);
    pinMode(p2Up, INPUT);
    pinMode(p2Down, INPUT);

    // delay(500);
    frame.addObject(ball);
    frame.addObject(playerLeft);
    frame.addObject(playerRight);

    ball.xVel = 8;
    ball.yVel = 8;

    playerLeft.height = 5;
    playerRight.height = 5;
    loadScore();
}

void loop()
{
    if (digitalRead(p1Up) == HIGH)
    {
        playerLeft.up();
    }
    if (digitalRead(p1Down) == HIGH)
    {
        playerLeft.down();
    }
    if (digitalRead(p2Up) == HIGH)
    {
        playerRight.up();
    }
    if (digitalRead(p2Down) == HIGH)
    {
        playerRight.down();
    }
    if (Serial.available() > 0)
    {
        char receivedChar = Serial.read(); // Read one character
        Serial.print("You pressed: ");
        Serial.println(receivedChar); // Echo back the character
        if (receivedChar == 'w' || digitalRead(p1Up) == HIGH)
        {
            playerLeft.up();
        }
        else if (receivedChar == 's')
        {
            playerLeft.down();
        }
        else if (receivedChar == 'i')
        {
            playerRight.up();
        }
        else if (receivedChar == 'k')
        {
            playerRight.down();
        }
    }
    // ball.right();
    // Serial.println(ball.pos().getX());
    // starter frame

    // Load all objects from the frame
    loadFrame();

    // Load both player scores
    if (p1OldScore != frame.p1Score || p2OldScore != frame.p2Score)
    {
        loadScore();
    }

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
        uint16_t bitRow = rows[currentRow]; // Repræsenterer første bitmønster
        uint16_t redPixels = 0;             // De røde pixels på rækken
        uint16_t greenPixels = 0;           // De grønne pixels på rækken
        // Behandl den aktuelle række i arrayet
        for (int i = 0; i < 16; i++)
        {
            switch (frame.grid[currentRow][i])
            {
            case 1: // Skal den være rød
                redPixels |= (1 << i);
                greenPixels |= (0 << i);
                break;
            case 2: // Skal den være grøn
                redPixels |= (0 << i);
                greenPixels |= (1 << i);
                break;
            case 3: // Skal den være orange
                redPixels |= (1 << i);
                greenPixels |= (1 << i);
                break;
            case 0: // Skal den ikke lyse
                redPixels |= (0 << i);
                greenPixels |= (0 << i);
                break;
            default:
                break;
            }
        }

        digitalWrite(latchPin, LOW);                          // Forbered latch
        shiftOut16(dataPin, clockPin, LSBFIRST, bitRow);      // Send the currently indexed row
        shiftOut16(dataPin, clockPin, MSBFIRST, redPixels);   // Send Val2
        shiftOut16(dataPin, clockPin, MSBFIRST, greenPixels); // Send Val3
        digitalWrite(latchPin, HIGH);                         // Aktivér latch for at opdatere output

        // Gå til næste række i arrayet    // delay(500);
    }
}

void loadScore()
{
    Serial.println("Load score");
    digitalWrite(latchPinScore, LOW);
    shiftOut(dataPinScore, clockPinScore, MSBFIRST, (frame.p2Score << 4) | frame.p1Score);
    digitalWrite(latchPinScore, HIGH);

    p1OldScore = frame.p1Score;
    p2OldScore = frame.p2Score;
}