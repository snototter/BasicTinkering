#include <BtSevenSegmentDisplay.h>

#define DELAY 1500
// Segments to show "--:--"
const uint8_t SEG_STRIKE[] = 
{
  BT_SSD_SEG_G,
  BT_SSD_SEG_G | BT_SSD_SEG_COLON,
  BT_SSD_SEG_G,
  BT_SSD_SEG_G
};

BtSevenSegmentDisplayTM1637 display(2, 3);

void setup() {}

void loop() {
  // Display "--:--"
  display.setSegments(SEG_STRIKE);
  delay(DELAY);

  // Display some numbers:
  // Note that the last two numbers are out
  // of display range and thus, won't be shown.
  int numbers[]= {0, 10, 100, 9009, 
    -1, -10, -100, -2000, 10000};
  for (int i = 0; i < 8; ++i)
  {
    display.displayInteger(numbers[i]);
    delay(DELAY);
  }

  // Display time
  for (int i = 0; i < 120; i += 15)
  {
    display.displayTime(i / 60, i % 60);
    delay(DELAY);
  }
  display.clear();
  delay(DELAY);

  // Set different brightness levels
  for (int i=0; i < 8; ++i)
  {
    display.setBrightness(i);
    // displayTime() doesn't check inputs:
    display.displayTime(88,99);
    delay(DELAY);
  }
}
