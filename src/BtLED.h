#ifndef __BASIC_TINKERING_LED__
#define __BASIC_TINKERING_LED__

/**
 * Wrapper for LEDs (supports blocking/non-blocking blinking).
 */
class BtLED
{
public:
  // Set the pin number upon construction.
  BtLED(uint8_t pin);

  // Returns current pin state.
  bool status() const;

  // Turn LED on.
  void on();

  // Turn LED off.
  void off();

  // Toggle on/off.
  void toggle();

  // Start non-blocking blinking (~"time" ms on,
  // ~"time" ms off). You must call blink() which
  // takes care of toggling the LED.
  void startBlinking(unsigned int time);

  // Loop iteration to be called repeatedly after
  // you set up blinking via start_blinking().
  void blink();

  // Disable blinking, once you're done.
  void stopBlinking();

  // Blocking call to blink n times ("time" ms on, "time" ms off).
  void blockingBlink(unsigned int time, unsigned int n);

  // Set a value [0, 255] directly. Ensure that the
  // LED is wired to a PWM pin!
  // See
  // https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
  // and
  // https://forum.arduino.cc/index.php?topic=79842.0
  void setValue(uint8_t value);

  // Configures the LED to be dimmed from now on.
  // Ensure that the LED is wired to a PWM pin!
  // See comments on setValue().
  // * Use value=0 to disable dimming.
  // * This call doesn't turn on/off the LED.
  void setDimValue(uint8_t value);

  // Slowly increase the brightness [0, 255] over
  // "time" milliseconds. Ensure that the LED is
  // wired to a PWM pin! See comments on setValue().
  void fadeIn(unsigned int time);

  // Slowly decrease brightness from 255 to 0 over
  // "time" milliseconds. Ensure that the LED is
  // wired to a PWM pin! See comments on setValue().
  void fadeOut(unsigned int time);

private:
  // Pin number (digital in).
  uint8_t pin_;

  // Internal state variable.
  uint8_t state_;

  // Stores the selected dim value (requires PWM pin,
  // see also setDimValue()).
  uint8_t dim_value_;

  // Number of milliseconds the LED should be
  // on or off while blinking.
  unsigned int blink_time_;

  // Last LED toggle while blinking.
  unsigned long blink_start_;
};
#endif
