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
#pragma once;

enum STATE{clockwise, counterClockwise, idle};

#define STATE_UP STATE::clockwise;
#define STATE_DOWN STATE::counterClockwise;
#define STATE_IDLE STATE::idle;
#define CLOCKWISE clockwise()
#define COUNTERCLOCKWISE counterClockwise()
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
     *
     * @param pinButton - pin number of the button pin
     * @param pinA - the pin number of pinA
     * @param pinB - the pin number of pinB
     * @param trackingValue - the initial value of the number that the encoder will change.
     * @param lowerLimit  - the lowest acceptable value of the number being tracked.
     * @param upperLimit  - the largest acceptable value of the number being tracked.
     */
    SimpleEncoder(int pinButton, int pinA, int pinB, long trackingValue, long lowerLimit, long upperLimit);

    /**
     * public methods
     */

    /**
     * Returns true if the encoder is moving in an upward direction.
     * @return bool
     */
    bool clockwise();

    /**
     * Returns true if the encoder is mofing in a downward direction;
     * @return bool
     */
    bool counterClockwise();

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
    long getValue();

    /**
     * Sets the value that you are tracking, must be within the established upper and lower values or it will not be set.
     * @param value - long newValue
     */
    void setValue(long newValue);

    /**
     * Change the lower and upper value that you want the encoder to track.
     * The newValue must be within the stated lower and upper limit or nothing
     * will be changed
     * @param lowerLimit - long
     * @param upperLimit - long
     * @param newValue - long
     */
    void setLimits(long lowerLimit, long upperLimit, long newValue);

private:
    int encA;
    int encB;
    int BTN;
    int encState;
    int lastState;
    long value;
    long lower;
    long upper;
    bool trackValue = false;

    STATE getState();
    void adjustValue();
};

#endif //SIMPLEENCODER_SIMPLEENCODER_H
