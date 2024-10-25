//
// Created by Mike Sims on 5/29/22.
//

#include <SimpleEncoder.h>

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB) {
    initPins(pinButton, pinA, pinB);
}

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue) {
    initPins(pinButton, pinA, pinB);
    value = trackingValue;
	valueSteps = 1;
	trackValue = true;
	checkLimits = false;
}

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue, float lowerLimit, float upperLimit) {
    initPins(pinButton, pinA, pinB);
    value = trackingValue;
    lower = lowerLimit;
    upper = upperLimit;
    valueSteps = 1;
    trackValue = true;
    checkLimits = true;
}

SimpleEncoder::SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue, float lowerLimit, float upperLimit, float steps) {
    initPins(pinButton, pinA, pinB);
    value = trackingValue;
    lower = lowerLimit;
    upper = upperLimit;
    valueSteps = steps;
    trackValue = true;
    checkLimits = true;
}

bool SimpleEncoder::clockwise() {
    return getState() == SE_STATE_RIGHT;
}

bool SimpleEncoder::right() {
    return getState() == SE_STATE_RIGHT;
}

bool SimpleEncoder::counterClockwise() {
    return getState() == SE_STATE_LEFT;
}

bool SimpleEncoder::left() {
    return getState() == SE_STATE_LEFT;
}

bool SimpleEncoder::changing() {
    return getState() != SE_STATE_IDLE;
}

bool SimpleEncoder::idle() {
    return getState() == SE_STATE_IDLE;
}

bool SimpleEncoder::buttonPressed() {
    return digitalRead(buttonPin) == LOW;
}

float SimpleEncoder::getValue() {
    getState();
    return value;
}

void SimpleEncoder::setValue(float newValue) {
	value = newValue;
}

void SimpleEncoder::adjustValue() {
    if (value > upper) {
        value = upper;
	}
    else if (value < lower) {
		value = lower;
	}
}

void SimpleEncoder::setLimits(float lowerLimit, float upperLimit) {
    lower = lowerLimit;
    upper = upperLimit;
    checkLimits = true;
}

void SimpleEncoder::setLimits(float lowerLimit, float upperLimit, float newValue) {
    lower = lowerLimit;
    upper = upperLimit;
    value = newValue;
    trackValue = true;
    checkLimits = true;
}

void SimpleEncoder::setSteps(float steps) {
    valueSteps = steps;
    trackValue = valueSteps != 0;
}

STATE SimpleEncoder::getState() {
    static STATE thisState = SE_STATE_IDLE;
    static int lastState = 0;
    int encAState = digitalRead(encA);
    int encBState = digitalRead(encB);
    if (encAState != lastState) {
        lastState = encAState;
        if (encBState != encAState) {
            if (trackValue) value += valueSteps;
            thisState = SE_STATE_RIGHT;
        }
        else {
            if (trackValue) value -= valueSteps;
            thisState = SE_STATE_LEFT;;
        }
        if (trackValue && checkLimits) adjustValue();
    }
    else {
        thisState = SE_STATE_IDLE;
    }
    return thisState;
}

/**
 * Private Methods
 */

void initPins(int pinButton, int pinA, int pinB) {
    encA = pinA;
    encB = pinB;
    buttonPin = pinButton;
    pinMode(encA, INPUT);
    pinMode(encB, INPUT);
    pinMode(buttonPin, INPUT_PULLUP);
}

