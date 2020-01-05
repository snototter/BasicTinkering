#include <BtStopWatch.h>

// This demo uses a millisecond-accurate stop watch:
BtStopWatchMillis stop_watch;

#define DELAY 500

void setup() 
{
  Serial.begin(9600);
  stop_watch.start();
}

void loop() 
{
  // * Each loop() iteration takes ~3 seconds.
  // * After each loop(), the stop watch will be
  //   toggled.
  Serial.print("Stop watch is");
  if (!stop_watch.isRunning())
    Serial.print(" NOT");
  Serial.println(" running.");
  
  Serial.print("  Elapsed ms: ");
  for (uint8_t i = 0; i < 3; ++i)
  {
    delay(DELAY);
    
    unsigned long elapsed = stop_watch.elapsed();
    
    if (i > 0)
      Serial.print(", ");
    if (i == 2)
      Serial.println(elapsed);
    else
      Serial.print(elapsed);
  }

  stop_watch.toggle();
}
