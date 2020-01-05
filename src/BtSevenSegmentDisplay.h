#ifndef __BASIC_TINKERING_SEVEN_SEGMENT_DISPLAY__
#define __BASIC_TINKERING_SEVEN_SEGMENT_DISPLAY__

/**
 * Bit codes to manually enable segments via
 * setSegments(). For example, to display 'H',
 * you would need: uint8_t seg = B | C | E | F | G;
 */
#define BT_SSD_SEG_A     0b00000001
#define BT_SSD_SEG_B     0b00000010
#define BT_SSD_SEG_C     0b00000100
#define BT_SSD_SEG_D     0b00001000
#define BT_SSD_SEG_E     0b00010000
#define BT_SSD_SEG_F     0b00100000
#define BT_SSD_SEG_G     0b01000000
#define BT_SSD_SEG_COLON 0b10000000


/**
 * If SSD_STORE_SEGMENTS is defined, the display
 * stores the currently displayed segments and can
 * be queried via getSegments(). If not defined,
 * you would save 4 bytes of precious memory ;-)
 */
#define SSD_STORE_SEGMENTS


/**
 * Utility for TM1637 4-digit 7-segment displays.
 */
class BtSevenSegmentDisplayTM1637
{
public:
  /**
   * Set up display:
   * ==> CLK and DIO must be connected to digital pins, specify pin
   *     numbers as pin_clk and pin_dio.
   * ==> Choose initial brightness in [0, 7].
   * ==> Adjust delay (in microseconds) between sending single bits
   *     to the I2C. 100 to 150 worked nicely for my tested displays.
   */
  BtSevenSegmentDisplayTM1637(uint8_t pin_clk, uint8_t pin_dio,
    uint8_t brightness = 7, unsigned long bit_delay = 100);

  /**
   * Set the display brightness in [0, 7].
   * Note that the brightness won't change until the next
   * displayX() call.
   */
  void setBrightness(uint8_t brightness);

  /**
   * Display an integer -999 <= x <= 9999, right-aligned.
   * Out-of-range values will silently be ignored, i.e.
   * simply not shown.
   */
  void displayInteger(int x);

  /**
   * Display a time, i.e. "a:b" (numbers will be zero-padded).
   * You are responsible of providing sane inputs (that is,
   * "99:99" would be displayed, too).
   * If either "a" or "b" is >= 100 (i.e. would require 3 digits),
   * the call is silently ignored, i.e. simply not shown.
   */
  void displayTime(uint8_t a, uint8_t b);

  /** Clear the display. */
  void clear();

  /**
   * Set the segments directly. Use only if you know what
   * you are doing!
   *
   * segments: raw values to send to the TM1637 chip.
   * num_digits: length of "segments"
   * first_pos: use this to align the displayed values, e.g.
   *     to center a two byte input, you would set first_pos = 1.
   */
  void setSegments(const uint8_t segments[], uint8_t num_digits = 4, uint8_t first_pos = 0);

  /** Returns the gfedcba segment encoding for hex digits (0-9, A-F) */
  uint8_t digitToSegment(uint8_t digit) const;

#ifdef SSD_STORE_SEGMENTS
  /**
   * Fills the input (4-element!) "segments" array with
   * the currently displayed segments. Note that this
   * won't work upon program start, i.e. you have to
   * display...() something first!
   */
  void getSegments(uint8_t segments[]) const;
#endif // SSD_STORE_SEGMENTS

private:
  /** Pin number for CLK. */
  uint8_t pin_clk_;

  /** Pin number for DIO. */
  uint8_t pin_dio_;

  /** Display brightness level in [0,7]. */
  uint8_t brightness_;

#ifdef SSD_STORE_SEGMENTS
  /** Buffer of last display...()ed segments. */
  uint8_t segments_[4];
#endif // SSD_STORE_SEGMENTS

  /** Delay in microseconds between sending bits to the display. */
  unsigned long bit_delay_;

  /** Delay between bits. */
  inline void bitDelay() const
  {
    delayMicroseconds(bit_delay_);
  }

  /** Set up DIO to prepare data transmission. */
  void start() const;

  /** Finalize data transmission. */
  void stop() const;

  /** Send a single byte to display. */
  bool sendByte(uint8_t byte) const;
};
#endif
