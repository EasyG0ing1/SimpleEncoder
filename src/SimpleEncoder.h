/*
 * SimpleEncoder is a simple and easy to use Arduino class for easy use of
 * rotary encoders.
 *
 * Written by - Michael Sims
 * Full documentation can be found at: https://github.com/EasyG0ing1/SimpleEncoder
 *
 * See LICENSE file for acceptable use conditions - this is open source
 * and there are no restrictions on its usage, I simply ask for some acknowledgment
 * if it is used in your project.
 */

#ifndef SIMPLEENCODER_SIMPLEENCODER_H
#define SIMPLEENCODER_SIMPLEENCODER_H
#include <Arduino.h>
#pragma once

enum STATE{ST_RIGHT, ST_LEFT, ST_IDLE};

#define STATE_RIGHT STATE::ST_RIGHT;
#define STATE_LEFT STATE::ST_LEFT;
#define STATE_IDLE STATE::ST_IDLE;
#define CLOCKWISE clockwise()
#define RIGHT right()
#define COUNTERCLOCKWISE counterClockwise()
#define LEFT left()
#define BUTTON_PRESSED buttonPressed()
#define CHANGING changing()
#define IDLE idle()
#define VALUE getValue()

class SimpleEncoder {

public:
    /**
     * Constructors
     * @param pinButton - pin number of the button pin
     * @param pinA - the pin number of pinA
     * @param pinB - the pin number of pinB
     */
    SimpleEncoder(int pinButton, int pinA, int pinB);

    /**
     * Constructors
     * @param pinButton - pin number of the button pin
     * @param pinA - the pin number of pinA
     * @param pinB - the pin number of pinB
     * @param trackingValue - the initial value of the number that the encoder will change.
     */
    SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue);

    /**
     * @param pinButton - pin number of the button pin
     * @param pinA - the pin number of pinA
     * @param pinB - the pin number of pinB
     * @param trackingValue - the initial value of the number that the encoder will change.
     * @param lowerLimit  - the lowest acceptable value of the number being tracked.
     * @param upperLimit  - the largest acceptable value of the number being tracked.
     */
    SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue, float lowerLimit, float upperLimit);

    /**
     * @param pinButton - pin number of the button pin
     * @param pinA - the pin number of pinA
     * @param pinB - the pin number of pinB
     * @param trackingValue - the initial value of the number that the encoder will change.
     * @param lowerLimit  - the lowest acceptable value of the number being tracked.
     * @param upperLimit  - the largest acceptable value of the number being tracked.
     * @param steps  - the value to increase or decrease trackingValue by..
     */
    SimpleEncoder(int pinButton, int pinA, int pinB, float trackingValue, float lowerLimit, float upperLimit, float steps);

    /**
     * public methods
     */

    /**
     * Returns true if the encoder is moving in an upward direction (right).
     * @return bool
     */
    bool clockwise();

    /**
     * Returns true if the encoder is moving in an upward direction (right).
     * @return bool
     */
    bool right();

    /**
     * Returns true if the encoder is mofing in a downward direction (left);
     * @return bool
     */
    bool counterClockwise();

    /**
     * Returns true if the encoder is mofing in a downward direction (left);
     * @return bool
     */
    bool left();

    /**
     * Returns true if the button is being pressed
     * @return bool
     */
    bool buttonPressed();

    /**
     * Returns true if the encoder is moving clockwise or counter clockwise
     * @return
     */
    bool changing();

    /**
     * Returns true if the encoder is not moving.
     * @return
     */
    bool idle();

    /**
     * Returns a long of the current vaklue being tracked.
     * @return long
     */
    float getValue();

    /**
     * Sets the value that you are tracking, must be within the established upper and lower values or it will not be set.
     * @param value - long newValue
     */
    void setValue(float newValue);

    /**
     * Change the lower and upper value that you want the encoder to track.
     * The newValue must be within the stated lower and upper limit or nothing
     * will be changed
     * @param lowerLimit - long
     * @param upperLimit - long
     */
    void setLimits(float lowerLimit, float upperLimit);

    /**
     * Change the lower and upper value that you want the encoder to track.
     * The newValue must be within the stated lower and upper limit or nothing
     * will be changed
     * @param lowerLimit - long
     * @param upperLimit - long
     * @param newValue - long
     */
    void setLimits(float lowerLimit, float upperLimit, float newValue);

    /**
     * Change the value of steps ... `value` will be incremented or decremented
     * each time the encoder is moved, by the numerical value of steps. For example, if
     * steps is set to 50, then turning the encoder will either increase or
     * decrease 'value' by 50. Get the current value of `value` by issuing encoder.VALUE.
     * Setting steps to 0 will disable any changes to value.
     *
     * @param steps - long
     */
    void setSteps(float steps);

private:
    int encA;
    int encB;
    int buttonPin;
    float value = 0.0;
    float lower = 0.0;
    float upper = 0.0;
    float valueSteps = 0.0;
    bool trackValue = false;
    bool checkLimits = true;

    STATE getState();
    void adjustValue();
};

#endif //SIMPLEENCODER_SIMPLEENCODER_H
