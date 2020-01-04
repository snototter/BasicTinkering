#include <Arduino.h>
#include <BtLED.h>

// Bit numbers for state variable
#define STATE_STATUS  0
#define STATE_BLINK   1


BtLED::BtLED(uint8_t pin) : pin_(pin), state_(0x00), dim_value_(0x00)
{
  pinMode(pin_, OUTPUT);
}

bool BtLED::status() const
{
  return bitRead(state_, STATE_STATUS);
}

void BtLED::on()
{
  if (dim_value_)
  {
    setValue(dim_value_);
  }
  else
  {
    digitalWrite(pin_, HIGH);
    bitWrite(state_, STATE_STATUS, HIGH);
  }
}

void BtLED::off()
{
  digitalWrite(pin_, LOW);
  bitWrite(state_, STATE_STATUS, LOW);
}

void BtLED::toggle()
{
  bitRead(state_, STATE_STATUS) ? off() : on();
}

void BtLED::startBlinking(unsigned int time)
{
  bitWrite(state_, STATE_BLINK, 1);
  blink_time_ = time;
  blink_start_ = millis();
  toggle();
}

void BtLED::blink()
{
  if (!bitRead(state_, STATE_BLINK))
    return;
  const unsigned long now = millis();
  if ((now - blink_start_) >= blink_time_)
  {
    toggle();
    blink_start_ = now;
  }
}

void BtLED::stopBlinking()
{
  off();
  bitWrite(state_, STATE_BLINK, 0);
}

void BtLED::blockingBlink(unsigned int time, unsigned int n)
{
  if (n == 0)
    return;
  on();
  for (unsigned int i = 0; i < 2*n-1; ++i)
  {
    delay(time);
    toggle();
  }
  delay(time);
  off();
}

void BtLED::setValue(uint8_t value)
{
  analogWrite(pin_, value);
  bitWrite(state_, STATE_STATUS, value > 0);
}

void BtLED::setDimValue(uint8_t value)
{
  dim_value_ = value;
}

void BtLED::fadeIn(unsigned int time)
{
  const unsigned int dt = time / (255 / 5);
  for (uint8_t brightness = 0; brightness < 255; brightness+=5)
  {
    setValue(brightness);
    delay(dt);
  }
  on();
}

void BtLED::fadeOut(unsigned int time)
{
  const unsigned int dt = time / (255 / 5);
  for (uint8_t brightness = 255; brightness > 0; brightness-=5)
  {
    setValue(brightness);
    delay(dt);
  }
  off();
}
