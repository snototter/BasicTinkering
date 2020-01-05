#include <BtLED.h>

// On Arduino Nano, pin D9 is one of the PWM-enabled pins (needed
// to demonstrate fading/dimming)
BtLED led(9);

#define DELAY 1000

void setup() {}

void loop()
{
  // Fade in to full brightness (blocking call)
  led.fadeIn(2000);
  // Keep LED at full brightness for some time
  delay(DELAY);
  // Fade out again
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
