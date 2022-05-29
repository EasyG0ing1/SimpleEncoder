#include <Arduino.h>
#include <SimpleEncoder.h>

/**
 * This example should run on any Uno compatible board.
 * Connect pin 10 to the button pin on your encoder.
 * Connect pin 11 to pin A on your encoder.
 * Connect pin 12 to pin B on your encoder.
 * Make sure your encoder ground pin is connected to ground.
 */

const int BTN = 10;
const int encA = 11;
const int encB = 12;
long startValue = 0;
long lowerValue = -1000;
long upperValue = 1000;

SimpleEncoder encoder(BTN, encA, encB, startValue, lowerValue, upperValue);

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (encoder.MOVING) {
        Serial.println("Current value is: " + String(encoder.VALUE));
    }
}
