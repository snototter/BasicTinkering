#ifndef __BASIC_TINKERING_POTENTIOMETER__
#define __BASIC_TINKERING_POTENTIOMETER__

#include <Arduino.h>

/** Resolution of the potentiometer wrapper.
 * By default, we use the default 10 bit resolution,
 * i.e. values are reported in [0, 1023].
 * Some boards support 12-bit resolution, see
 * https://www.arduino.cc/reference/en/language/functions/analog-io/analogread/
 * and change BT_ADC_RESOLUTION accordingly.
 */
#define BT_ADC_RESOLUTION 1024

/**
 * Wrapper for potentiometers.
 *
 * Template parameter NUM_BINS is used
 * to bin the potentiometer values into
 * bins/sectors. You have to ensure that
 * 0 < NUM_BINS <= BT_ADC_RESOLUTION.
 */
template <uint16_t NUM_BINS>
class BtPotentiometer
{
public:
  /** Set the pin number upon construction. */
  BtPotentiometer(uint8_t pin) : pin_(pin) {}

  /** Returns the current value. */
  uint16_t readValue() const
  {
    return analogRead(pin_);
  }

  /** Returns the current bin. */
  uint16_t readBin() const
  {
    return analogRead(pin_) / (BT_ADC_RESOLUTION / NUM_BINS);
  }

  /** Returnt the templated number of bins. */
  uint16_t numBins() const
  {
    return NUM_BINS;
  }

private:
  /** Pin number (analog in). */
  uint8_t pin_;
};


/**
 * Convenience function to check if two values differ more than
 * a given threshold.
 */
inline bool potentiometerChanged(uint16_t current, uint16_t previous, uint16_t threshold=10)
{
  if (current > previous)
    return (current - previous) > threshold;
  return (previous - current) > threshold;
}
#endif
