#include <BtPotentiometer.h>

// We connect a potentiometer at (5V, GND, and) analog A1 (pin 15).
// Additionally, we want to split the potentiometer's range
// into 5 bins.
BtPotentiometer<5> poti(15);

uint16_t prev_value = 65535;

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  // Read current value and print to serial monitor if changed.
  const uint16_t value = poti.readValue();
  if (potentiometerChanged(value, prev_value, 5))
  {
    prev_value = value;
    Serial.print("Poti value: ");
    Serial.print(value);
    Serial.print(", bin ");
    Serial.println(poti.readBin());
  }
  delay(200);
}
