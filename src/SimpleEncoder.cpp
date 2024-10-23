//
// Created by Mike Sims on 5/29/22.
//

#include <SimpleEncoder.h>

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB) {
    encA = pinA;
    encB = pinB;
    buttonPin = pinButton;
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue) {
    encA = pinA;
    encB = pinB;
    buttonPin = pinButton;
    value = trackingValue;
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue, float lowerLimit, float upperLimit) {
    encA = pinA;
    encB = pinB;
    buttonPin = pinButton;
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    value = trackingValue;
    lower = lowerLimit;
    upper = upperLimit;
    valueSteps = 1;
    trackValue = valueSteps != 0;
    checkLimits = (lower != upper) && (lower != 0.0 && upper != 0);
}

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue, float lowerLimit, float upperLimit, float steps) {
    encA = pinA;
    encB = pinB;
    buttonPin = pinButton;
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
    value = trackingValue;
    lower = lowerLimit;
    upper = upperLimit;
    valueSteps = steps;
    trackValue = valueSteps != 0;
    checkLimits = (lower != upper) && (lower != 0.0 && upper != 0);
}

bool SimpleEncoder::clockwise() {
    return getState() == STATE_RIGHT;
}

bool SimpleEncoder::right() {
    return getState() == STATE_RIGHT;
}

bool SimpleEncoder::counterClockwise() {
    return getState() == STATE_LEFT;
}

bool SimpleEncoder::left() {
    return getState() == STATE_LEFT;
}

bool SimpleEncoder::buttonPressed() {
    return digitalRead(buttonPin) == LOW;
}

float SimpleEncoder::getValue() {
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

void SimpleEncoder::setValue(float newValue) {
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

void SimpleEncoder::setLimits(float lowerLimit, float upperLimit) {
    lower = lowerLimit;
    upper = upperLimit;
    checkLimits = (lower != upper) && (lower != 0.0 && upper != 0);
}

void SimpleEncoder::setLimits(float lowerLimit, float upperLimit, float newValue) {
    lower = lowerLimit;
    upper = upperLimit;
    value = newValue;
    trackValue = valueSteps != 0;
    checkLimits = (lower != upper) && (lower != 0.0 && upper != 0);
}

void SimpleEncoder::setSteps(float steps) {
    valueSteps = steps;
    trackValue = valueSteps != 0;
}

STATE SimpleEncoder::getState() {
    static STATE thisState = STATE_IDLE;
    static int lastState = 0;
    int encAState = digitalRead(encA);
    int encBState = digitalRead(encB);
    if (encAState != lastState) {
        lastState = encAState;
        if (encBState != encAState) {
            if (trackValue) value += valueSteps;
            thisState = STATE_RIGHT;
        }
        else {
            if (trackValue) value -= valueSteps;
            thisState = STATE_LEFT;;
        }
        if (trackValue && checkLimits) adjustValue();
    }
    else {
        thisState = STATE_IDLE;
    }
    return thisState;
}

