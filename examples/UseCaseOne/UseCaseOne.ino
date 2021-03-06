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

SimpleEncoder encoder(BTN, encA, encB);

void setup() {
    Serial.begin(9600);
}

void loop() {
    if (encoder.CLOCKWISE) {
        Serial.println("Encoder moving clockwise");
    }
    if (encoder.COUNTERCLOCKWISE) {
        Serial.println("Encoder moving counter clockwise");
    }
    if (encoder.BUTTON_PRESSED) {
        Serial.println("Button Pressed");
    }
}
