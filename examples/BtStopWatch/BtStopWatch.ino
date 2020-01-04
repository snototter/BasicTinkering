#include <BtStopWatch.h>

// This demo uses a millisecond-accurate stop watch:
BtStopWatchMillis stop_watch;

void setup() 
{
  Serial.begin(9600);
  stop_watch.start();
}

void loop() 
{
  unsigned long elapsed = stop_watch.elapsed();
  Serial.print("Stop watch is");
  if (!stop_watch.isRunning())
    Serial.print(" NOT");
  Serial.println(" running.");
  Serial.print("  Elapsed ms: ");
  Serial.print(elapsed);
  delay(1000);

  Serial.print(", ");
  Serial.print(stop_watch.elapsed());
  delay(1000);

  Serial.print(", ");
  Serial.println(stop_watch.elapsed());
  delay(1000);

  stop_watch.toggle();
}
