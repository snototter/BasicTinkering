#include <BtButton.h>

// We connect two buttons at D6 and D7
BtButton btn1(6, 50, 500, false); // Will be very verbose upon being held
BtButton btn2(7);        // Will only notify us once for every hold event

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  btn1.read();
  // If you want to do something only once the user presses the button,
  // we need to check changed(), then isPressed(). Alternatively, we
  // could use if (changedToPressed()) { <do something> }.
  // btn1.isPressed() returns true as long as the button is pressed!
  if (btn1.changed())
  {
    if (btn1.isPressed())
      Serial.println("Button 1 PRESSED");
    else
      Serial.println("Button 1 R");
  }
  
  btn2.read();
  if (btn2.changed())
  {
    if (btn2.isPressed())
      Serial.println("Button 2 PRESSED");
    else
      Serial.println("Button 2 R");
  }

  // We can also check if a button is held
  if (btn1.isHeld())
    Serial.println("Button 1 is on hold!");
  if (btn2.isHeld())
    Serial.println("Button 2 is on hold!");
}
