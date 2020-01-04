#include <BtPotentiometer.h>

// We connect a potentiometer at (5V, GND, and) A1.
// Split the potentiometer's range into 5 bins.
BtPotentiometer<5> poti(15);

uint16_t prev_value = 65535;

void setup()
{
  Serial.begin(9600);
}

bool changed(uint16_t val)
{
  if (val > prev_value)
    return (val - prev_value) > 5;
  return (prev_value - val) > 5;
}

void loop()
{
  const uint16_t value = poti.readValue();
  if (changed(value))
  {
    prev_value = value;
    Serial.println("New value & bin:");
    Serial.println(value);
    Serial.println(poti.readBin());
    //Serial.println(poti.numBins());
  }
  delay(200);
}
