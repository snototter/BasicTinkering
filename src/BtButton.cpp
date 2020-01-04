#include <Arduino.h>
#include <BtButton.h>

// Bit numbers
#define STATE_CURRENT  0
#define STATE_PREVIOUS 1
#define STATE_CHANGED  2
#define STATE_SCAN     3
#define STATE_INVERT   4

// Store if we should notify once or continuously
#define STATE_HOLD_NOTIFY_ONCE 5
// Store if we should notify of a hold now
#define STATE_HOLD_NOTIFY   6
// Store if we already notified of a hold now
#define STATE_HOLD_NOTIFIED 7

BtButton::BtButton(uint8_t pin, unsigned int debounce_delay, unsigned int hold_delay,
  bool notify_hold_once) : pin_(pin), state_(0x00), debounce_delay_(debounce_delay),
  debounce_start_(millis()), hold_delay_(hold_delay)
{
  bitWrite(state_, STATE_HOLD_NOTIFY_ONCE, notify_hold_once);

  pinMode(pin_, INPUT_PULLUP);
  // TODO add parameter whether to use the internal pullup or not
  // If we use the pullup, we must invert the readings
  bitWrite(state_, STATE_INVERT, 1);
  bitWrite(state_, STATE_CURRENT, bitRead(state_, STATE_CURRENT) ^ bitRead(state_, STATE_INVERT));
  bitWrite(state_, STATE_PREVIOUS, bitRead(state_, STATE_CURRENT));

  //Serial.println("After init:");
  //Serial.println(bitRead(state_, STATE_CURRENT));
  //Serial.println(bitRead(state_, STATE_PREVIOUS));
}

bool BtButton::read()
{
  const unsigned long now = millis();
  const int scan = digitalRead(pin_);

  if (scan != bitRead(state_, STATE_SCAN))
    debounce_start_ = now;

  bitWrite(state_, STATE_SCAN, scan);
  bitWrite(state_, STATE_CHANGED, 0);
  bitWrite(state_, STATE_HOLD_NOTIFY, 0);

  if ((now - debounce_start_) > debounce_delay_)
  {
    // Button is debounced, now we can store the actual state
    // Remember the previous state...
    bitWrite(state_, STATE_PREVIOUS, bitRead(state_, STATE_CURRENT));
    // ... and store the current state (invert if necessary)
    bitWrite(state_, STATE_CURRENT, scan ^ bitRead(state_, STATE_INVERT));

    //Serial.println("After debounce:");
    //Serial.println(scan);
    //Serial.println(bitRead(state_, STATE_CURRENT));
    //Serial.println(bitRead(state_, STATE_PREVIOUS));

    const uint8_t changed = bitRead(state_, STATE_CURRENT) != bitRead(state_, STATE_PREVIOUS);
    bitWrite(state_, STATE_CHANGED, changed);

    // Check if button is being held
    if (bitRead(state_, STATE_CURRENT))
    {
      // Start counting towards isHeld() if we started pressing
      // the button right now:
      if (changed)
        hold_start_ = now;

      const bool held = (now - hold_start_) > hold_delay_;
      if (held )
      {
        if (!bitRead(state_, STATE_HOLD_NOTIFY_ONCE) | !bitRead(state_, STATE_HOLD_NOTIFIED))
        {
          bitWrite(state_, STATE_HOLD_NOTIFY, 1);
          bitWrite(state_, STATE_HOLD_NOTIFIED, 1);
        }
      }
      else
        bitWrite(state_, STATE_HOLD_NOTIFIED, 0);

    }
  }

  return bitRead(state_, STATE_CURRENT);
}

bool BtButton::isPressed() const
{
  return bitRead(state_, STATE_CURRENT);
}

bool BtButton::isHeld() const
{
  return bitRead(state_, STATE_HOLD_NOTIFY);
}

bool BtButton::changed() const
{
  return bitRead(state_, STATE_CHANGED);
}

bool BtButton::changedToPressed() const
{
  return bitRead(state_, STATE_CHANGED) & bitRead(state_, STATE_CURRENT);
}

