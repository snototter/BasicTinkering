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
  // btn1.isPressed() returns true as long as the button is pressed.
  // Thus, if you want to do something only once for each button press,
  // you need to check changed(), followed by isPressed() as follows:
  if (btn1.changed())
  {
    if (btn1.isPressed())
      Serial.println("Button 1 pressed");
    else
      Serial.println("Button 1 released");
  }
  //  Alternatively, you could use:
  //  if (btn1.changedToPressed()) { <do something> }
  
  btn2.read();
  if (btn2.changed())
  {
    if (btn2.isPressed())
      Serial.println("Button 2 pressed");
    else
      Serial.println("Button 2 released");
  }

  // We can also check if a button is held:
  if (btn1.isHeld())
    Serial.println("Button 1 is being held!");
  if (btn2.isHeld())
    Serial.println("Button 2 is being held!");
}
