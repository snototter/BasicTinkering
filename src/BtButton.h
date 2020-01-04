#ifndef __BASIC_TINKERING_BUTTON__
#define __BASIC_TINKERING_BUTTON__

/**
 * Utility for software-debounced buttons.
 */
class BtButton
{
public:
  // pin:              Pin number
  // debounce_delay:   How many milliseconds to wait for stabilization of
  //                   button signal. Set to 0 to disable/use a hardware-
  //                   debounce (e.g. Schmitt trigger).
  // hold_delay:       The button must be pressed for X milliseconds before
  //                   isHeld() will return true.
  // notify_hold_once: If true, isHeld() returns true only once (unless button
  //                   is released and pressed again). Otherwise, isHeld()
  //                   returns true as long as the button is pressed.
  BtButton(uint8_t pin, unsigned int debounce_delay = 50,
    unsigned int hold_delay = 500, bool notify_hold_once = true);

  // Must be invoked in every loop iteration to scan the button's pin.
  // Returns true if the button is currently pressed.
  bool read();

  // Returns the current state of the button.
  // Invoke after read().
  // This will return true as long as the button is pressed!
  bool isPressed() const;

  // Returns true if the button is currently active and has
  // been pressed for the configured minimum amount of time.
  bool isHeld() const;

  // Returns true if the button state changed.
  // Invoke after read().
  bool changed() const;

  // For convenience: returns true only for the first time after the user
  // pressed the button. Basically just returns changed() && isPressed().
  bool changedToPressed() const;

private:
  // Pin number (digital in)
  uint8_t pin_;

  // Internal state variable
  uint8_t state_;

  // How long to wait for signal stabilization
  unsigned int debounce_delay_;

  // Time stamp of last signal change
  unsigned long debounce_start_;

  // How long to wait before considering isHeld() to be true
  unsigned int hold_delay_;

  // Time stamp of last button down
  unsigned long hold_start_;
};
#endif
