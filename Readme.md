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
    if (encoder.CLOCKWISE) {
        //Code for upward motion
    }
    if (encoder.COUNTERCLOCKWISE) {
        //Code for downward motion
    }
}
```

## Value Tracking

You can have SimpleEncoder track a value for you which gets incremented or decremented based on the
direction of the encoder at the moment you check it.

```c++
#include <SimpleEncoder.h>

const int BUTTON_PIN = 10;
const int PINA = 11;
const int PINB = 12;
long myValue = 0;
long minValue = -100;
long maxValue = 100;

SimpleEncoder encoder(BUTTON_PIN, PINA, PINB, myValue, minValue, maxValue);
```

Then simply query the library for any changes in the encoder and if they exist, get the new value

```c++
void loop() {
    if(encoder.CHANGING) {
        myValue = encoder.VALUE;
    }
}
```

If you want to start tracking a value after you've already created your encoder, OR if you wish to alter
the upper and lower limits, you can do it like this:

```c++
encoder.setLimits(lowerLimit, upperLimit, newValue);
```

You can also set the value to a specific number at any time, but it must be a number that is within
the lower and upper limit:
```c++
encoder.setValue(newValue);
```

It's just that easy. 

There are two example sketches that show how to use the library.

These are the public methods in the library:

```
clockwise() - Returns true if rotary moving clockwise
counterClockwise() - Returns true if rotary moving counter clockwise
buttonPressed() - Button was pressed
changing() - rotary is moving in either direction
idle() - rotary is idle and not changing
getValue() - get the value of the variable being tracked
```

And these are the alternate MACROS that can be used instead of the method names:

```
CLOCKWISE - Returns true if rotary moving clockwise
COUNTERCLOCKWISE - Returns true if rotary moving counter clockwise
BUTTON_PRESSED - Button was pressed
CHANGING - rotary is moving in either direction
IDLE - rotary is idle and not changing
VALUE - get the value of the variable being tracked
```

Make sure that your encoder has 5v connected to it - usually sourced from the Arduino, and that
Pin C is connected to ground or things won't work properly.

Here is a schematic of how your rotary encoder should be connected. The yellow nodes
indicate where the encoder should be connected to the Arduino in accordance
with this library. 

![Schematic](./img/Schematic1.png)

If you're interested, [I made a PCB breakout board](https://oshwlab.com/sims.mike/rotaryencoderbasic) that I've already ordered and tested and it works perfectly.


Enjoy!