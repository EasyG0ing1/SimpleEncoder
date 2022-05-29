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

enum STATE{up, down, idle};

#define STATE_UP STATE::up;
#define STATE_DOWN STATE::down;
#define STATE_IDLE STATE::idle;
#define UP up()
#define DOWN down()
#define BUTTON buttonPressed()
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
    bool up();

    /**
     * Returns true if the encoder is mofing in a downward direction;
     * @return bool
     */
    bool down();

    /**
     * Returns true if the button is being pressed
     * @return bool
     */
    bool buttonPressed();

    /**
     * Returns true if the encoder is moving up or down
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
};

#endif //SIMPLEENCODER_SIMPLEENCODER_H
