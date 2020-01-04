#ifndef __BASIC_TINKERING_SEVEN_SEGMENT_DISPLAY__
#define __BASIC_TINKERING_SEVEN_SEGMENT_DISPLAY__

// Bit codes to enable different digit segments via setSegments.
#define BT_SSD_SEG_A     0b00000001
#define BT_SSD_SEG_B     0b00000010
#define BT_SSD_SEG_C     0b00000100
#define BT_SSD_SEG_D     0b00001000
#define BT_SSD_SEG_E     0b00010000
#define BT_SSD_SEG_F     0b00100000
#define BT_SSD_SEG_G     0b01000000
#define BT_SSD_SEG_COLON 0b10000000

// If defined, the display will store the currently displayed segments
// and you can query them via getSegments(). Otherwise, you can save
// 4 bytes of precious memory.
#define SSD_STORE_SEGMENTS

/**
 * Utility for 4-digit 7-segment displays using TM1637.
 */
class BtSevenSegmentDisplayTM1637
{
public:
  // * CLK and DIO must be connected to digital pins
  // * Choose initial brightness in [0, 7]
  // * Adjust delay (in microseconds) for sending bits to the I2C
  //   100 worked nicely for my tested displays.
  BtSevenSegmentDisplayTM1637(uint8_t pin_clk, uint8_t pin_dio,
    uint8_t brightness = 7, unsigned long bit_delay = 100);

  // Set the brightness in [0, 7], has an effect upon next display update.
  void setBrightness(uint8_t brightness);

  // Display the integer -999 <= x <= 9999, right-aligned.
  void displayInteger(int x);

  // Display a time, i.e. a:b (numbers will be zero-padded).
  // You are responsible of providing sane inputs (that is,
  // "99:99" would be displayed, too).
  void displayTime(uint8_t a, uint8_t b);

  // Clear the display
  void clear();

  // Set the segments directly
  void setSegments(const uint8_t segments[], uint8_t num_digits = 4, uint8_t first_pos = 0);

  // Get segment gfedcba encoding for digits 0-9, A-F
  uint8_t digitToSegment(uint8_t digit) const;

#ifdef SSD_STORE_SEGMENTS
  // Fills the (4-element!) segments array with the currently displayed
  // segments. Note that this won't work upon program start, i.e. you
  // have to display...() something first!
  void getSegments(uint8_t segments[]) const;
#endif // SSD_STORE_SEGMENTS

private:
  // Pin number for CLK
  uint8_t pin_clk_;

  // Pin number for DIO
  uint8_t pin_dio_;

  // Display brightness level in [0,7]
  uint8_t brightness_;

#ifdef SSD_STORE_SEGMENTS
  uint8_t segments_[4];
#endif // SSD_STORE_SEGMENTS

  // Delay in microseconds for sending bits to the I2C
  unsigned long bit_delay_;

  // Delay
  inline void bitDelay() const
  { delayMicroseconds(bit_delay_); }

  // Set up DIO to prepare data transmission
  void start() const;

  // Finalize data transmission
  void stop() const;

  // Send a single byte to I2C
  bool sendByte(uint8_t byte) const;
};
#endif
