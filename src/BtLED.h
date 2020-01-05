#ifndef __BASIC_TINKERING_LED__
#define __BASIC_TINKERING_LED__

/**
 * Wrapper for LEDs (supports blocking/non-blocking blinking)
 * and dimming/fading (if wired to a PWM-enabled pin).
 */
class BtLED
{
public:
  /** Set the pin number upon construction. */
  BtLED(uint8_t pin);

  /** Returns current pin state, true (HIGH) or false (LOW). */
  bool status() const;

  /**
   * Turn LED on.
   * If you setDimValue() before, LED will only light up with
   * the corresponding brightness (if pin is PWM-enabled).
   */
  void on();

  /** Turn LED off. */
  void off();

  /** Toggle on/off. */
  void toggle();

  /**
   * Start non-blocking blinking, i.e. LED will
   * be ~"time" ms on then ~"time" ms off.
   * You must call blink() in each loop() iteration
   * to allow the LED to toggle.
   */
  void startBlinking(unsigned int time);

  /**
   * Loop iteration to be called repeatedly after
   * you set up blinking via start_blinking().
   */
  void blink();

  /** Disable blinking, once you're done. */
  void stopBlinking();

  /** Blocking call to blink N times ("time" ms on, "time" ms off). */
  void blockingBlink(unsigned int time, unsigned int n);

  /**
   * Set a brightness value [0, 255] directly. Ensure that the
   *  LED is wired to a PWM pin!
   *  This brightness value will only be set once. If you want to
   *  keep the same brightness across several on/toggle/off-cycles,
   *  use setDimValue() instead!
   *  See
   *  https://www.arduino.cc/reference/en/language/functions/analog-io/analogwrite/
   *  and
   *  https://forum.arduino.cc/index.php?topic=79842.0
   */
  void setValue(uint8_t value);

  /**
   * Configures the LED to be dimmed from now on.
   * Ensure that the LED is wired to a PWM pin!
   * See comments on setValue().
   * => Use value=0 to disable dimming.
   * => This call doesn't turn on/off the LED.
   */
  void setDimValue(uint8_t value);

  /**
   * Slowly increase the brightness [0, 255] over
   * "time" milliseconds. Ensure that the LED is
   * wired to a PWM pin! See comments on setValue().
   */
  void fadeIn(unsigned int time);

  /**
   * Slowly decrease brightness from 255 to 0 over
   * "time" milliseconds. Ensure that the LED is
   * wired to a PWM pin! See comments on setValue().
   */
  void fadeOut(unsigned int time);

private:
  /** Pin number (digital in, preferably PWM-enabled
   * to support fading/dimming). */
  uint8_t pin_;

  /** Internal state variable. */
  uint8_t state_;

  /** Stores the selected dim value (requires PWM pin,
   * see also setDimValue()). */
  uint8_t dim_value_;

  /**
   * Number of milliseconds the LED should be
   * on or off while blinking. */
  unsigned int blink_time_;

  /** Time point we last toggled the LED while blinking. */
  unsigned long blink_start_;
};
#endif
