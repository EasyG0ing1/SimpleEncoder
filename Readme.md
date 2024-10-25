# SimpleEncoder

SimpleEncoder is a very simple, easy to use library for using rotary encoders with an Arduino.

To use it, you simply invoke the library by passing in the pin assignments from your encoder.

```c++
#include <SimpleEncoder.h>

const int BUTTON_PIN = 10;
const int PINA = 11;
const int PINB = 12;

SimpleEncoder encoder(BUTTON_PIN, PINA, PINB);
```

The library handles configuring the pins for you. Then to use the encoder, you can engage the library
in a couple of different ways, all of which need to be in your loop method.

```c++
void loop() {
    if (encoder.RIGHT) {
        //Code for upward motion
    }
    if (encoder.LEFT) {
        //Code for downward motion
    }
    if (encoder.CHANGING) {
        //Code for when the encoder is moving in any direction.
    }
}
```

## Value Tracking

You can have SimpleEncoder track a value for you which gets incremented or decremented based on the
direction of the encoder. You can also set the number of `steps` which the value should be incremented or decremented by.

```c++
#include <SimpleEncoder.h>

const int BUTTON_PIN = 10;
const int PINA = 11;
const int PINB = 12;
long myValue = 0;
long minValue = -100;
long maxValue = 100;
long steps = 5;

SimpleEncoder encoder(BUTTON_PIN, PINA, PINB, myValue, minValue, maxValue);
SimpleEncoder encoder(BUTTON_PIN, PINA, PINB, myValue, minValue, maxValue, steps);
```
** Steps feature was recently added. Increase or decrease your value by the number of steps specified.
Then simply query the library for the new value.

```c++
void loop() {
    if(encoder.CHANGING) {
        myValue = encoder.VALUE;
    }
}
```

If you aren't checking the encoder for motion, the value will not change. The only way the value can change
is when the methods are called to see if the encoder is moving.

If you want to start tracking a value after you've already created your encoder, OR if you wish to alter
the upper and lower limits, or the step value, you can do it like this:

```c++
encoder.setValue(newValue);
encoder.setLimits(lowerLimit, upperLimit);
encoder.setLimits(lowerLimit, upperLimit, newValue);
encoder.setSteps(newValue);
```

**All datatypes related to tracking a value are float datatypes. This allows for fractional number value tracking and steps**

There are three example sketches that show how to use the library.

These are the public methods in the library:

| Method          | Description                              |
|-----------------|------------------------------------------|
| right()         |  Returns true if rotary is turning right ||
| left()          | Returns true if rotary is turning left|
| buttonPressed() | Returns true if the button was pressed|
| changing()      | Returns true if the rotary is moving in either direction|
| idle()          | Returns true it the rotary is idle and not changing|
| getValue()      | Returns a float having the value of the variable being tracked|
| setValue(value) | set the value of the encoders tracked variable|
| setSteps(value) | change the value of the step variable|
| setLimits()     | change the variable limits (see example above)|


And these are the alternate MACROS that can be used instead of the method names:

|MACRO|Description|
|-----|-----------|
|RIGHT|Returns true if rotary is turning right|
|LEFT|Returns true if rotary is turning left|
|CHANGING|rotary is moving in either direction|
|BUTTON_PRESSED|Returns true if the button was pressed|
|IDLE|Returns a float having the value of the variable being tracked|
|VALUE|get the value of the variable being tracked|

Make sure that your encoder has 5v or 3.3V connected to it - usually sourced from the Arduino, and that
Pin C is connected to ground or things won't work properly.

Here is a schematic of how your rotary encoder should be connected. The yellow nodes
indicate where the encoder should be connected to the Arduino in accordance
with this library. 

![Schematic](./img/Schematic1.png)

If you're interested, [I made a PCB breakout board](https://oshwlab.com/sims.mike/rotaryencoderbasic) that I've already ordered and tested and it works perfectly.


Enjoy!

## Change Log

* 1.2.1 - Bug fixes and streamlined some code.

* 1.2.0 - Added steps and modified the code for efficiency. Added right and left methods to be used instead of 
          clockwise and counterClockwise respectively. Changed all variables related to tracking a value to float
          datatypes to facilitate fractional number tracking.