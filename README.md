# BasicTinkering Library
A collection of wrapper classes for commonly used electronic components. Quite useful for tinkering and keeping projects slightly more maintainable.
`BasicTinkering` can be installed via Arduino's Library Manager (Arduino IDE: `Sketch > Include Library > Manage Libraries`).

This library includes wrappers for:
* `BtButton` - software-debounced push-buttons/triggers.
* `BtLED` - standard on/off plus blinking/fading capabilities (if LED is wired to a PWM-enabled pin).
* `BtPotentiometer` (templated class) - allows querying and binning the potentiometer value.
* `BtSevenSegmentDisplay` - 7-segment display wrappers currently supporting `TM1637` digital tubes (4-digit with colon).
* `BtStopWatch` (templated class) - measures time.

