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

bool SimpleEncoder::clockwise() {
    return getState() == STATE_UP;
}

bool SimpleEncoder::counterClockwise() {
    return getState() == STATE_DOWN;
}

bool SimpleEncoder::buttonPressed() {
    return digitalRead(BTN) == LOW;
}

long SimpleEncoder::getValue() {
    if (trackValue) {
        getState();
        return value;
    }
    return 0;
}

bool SimpleEncoder::changing() {
    return getState() != STATE_IDLE;
}

bool SimpleEncoder::idle() {
    return getState() == STATE_IDLE;
}

void SimpleEncoder::setValue(long newValue) {
    if((newValue >= lower) && (newValue <= upper)) {
        value = newValue;
    }
}

void SimpleEncoder::adjustValue() {
    if (value > upper)
        value = upper;
    else
        if (value < lower)
            value = lower;
}

void SimpleEncoder::setLimits(long lowerLimit, long upperLimit, long newValue) {
    if ((newValue >= lowerLimit) && (newValue <= upperLimit)) {
        lower = lowerLimit;
        upper = upperLimit;
        value = newValue;
        trackValue = true;
    }
}

STATE SimpleEncoder::getState() {
    encState = digitalRead(encA);
    if (encState != lastState) {
        lastState = encState;
        if (digitalRead(encB) != encState) {
            if (trackValue) value += 1;
            adjustValue();
            return STATE_UP;
        }
        else {
            if (trackValue) value -= 1;
            adjustValue();
            return STATE_DOWN;
        }
    }
    return STATE_IDLE;
}

