#include <BtLED.h>

#define DELAY 1000

BtLED led(9);
void setup() {}

void loop()
{
  // Fading
  led.fadeIn(2000);
  delay(DELAY);
  led.fadeOut(1000);
  delay(DELAY);

  // Blocking call to blink 3 times
  led.blockingBlink(300, 3);

  // Classic usage
  led.on();
  delay(DELAY);
  led.off();
  delay(DELAY);

  // Non-blocking blinking calls:
  led.startBlinking(500);
  for (int i = 0; i < 500; ++i)
  {
    led.blink();
    delay(10);
  }
  led.stopBlinking();
}
