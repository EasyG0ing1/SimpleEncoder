//
// Created by Mike Sims on 5/29/22.
//

#include <SimpleEncoder.h>

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB) {
    encA = pinA;
    encB = pinB;
    BTN = pinButton;
    lastState = digitalRead(encA);
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(BTN, INPUT_PULLUP);
}

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB, long trackingValue, long lowerLimit, long upperLimit) {
    encA = pinA;
    encB = pinB;
    BTN = pinButton;
    lastState = digitalRead(encA);
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(BTN, INPUT_PULLUP);
    value = trackingValue;
    trackValue = true;
    lower = lowerLimit;
    upper = upperLimit;
}

bool SimpleEncoder::up() {
    getState();
    return state == UP;
}

bool SimpleEncoder::down() {
    getState();
    return state == DOWN;
}

bool SimpleEncoder::buttonPressed() {
    return digitalRead(BTN) == LOW;
}

long SimpleEncoder::getValue() {
    getState();
    return trackValue ? value : 0;
}

bool SimpleEncoder::changing() {
    getState();
    return state != STATE_IDLE;
}

bool SimpleEncoder::idle() {
    getState();
    return state == STATE_IDLE;
}

void SimpleEncoder::getState() {
    state = STATE_IDLE;
    encState = digitalRead(encA);
    if (encState != lastState) {
        if (digitalRead(encA) != encState) {
            state = UP;
            if (trackValue) value++;
        }
        else {
            state = DOWN;
            if (trackValue) value--;
        }
    }
    if (trackValue) {
        if (value >= upper) value = upper;
        if (value <= lower) value = lower;
    }
}