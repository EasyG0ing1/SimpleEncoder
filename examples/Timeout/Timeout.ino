/**
 * This sketch demonstrates a usage scenario where you might desire to execute code
 * after a period of time has passed when the user has not engaged the encoder.
 */
#include <Arduino.h>
#include <SimpleEncoder.h>
#include <BlockNot.h>

// Set these pin numbers according to what is actually connected to your arduino.
const int BUTTON = 10;
const int PIN_A = 11;
const int PIN_B = 12;
const int LED = 9;

SimpleEncoder encoder(BUTTON, PIN_A, PIN_B);

BlockNot timeout(60, SECONDS);

void setup() {
    pinMode(LED, OUTPUT);
}

void loop() {
    if(encoder.CLOCKWISE) {
        timeout.RESET;
        digitalWrite(LED, LOW);
        //Code to execute if encoder turned clockwise.
    }
    if(encoder.COUNTERCLOCKWISE) {
        timeout.RESET;
        digitalWrite(LED, LOW);
        //Code to execute if encoder turned counterclockwise.
    }
    if(encoder.BUTTON_PRESSED) {
        timeout.RESET;
        digitalWrite(LED, LOW);
        //Code to execute if the encoder button is pressed.
    }
    if(timeout.TRIGGERED) {
        digitalWrite(LED, HIGH);
    }
}