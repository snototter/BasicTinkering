#include <BtStopWatch.h>

BtStopWatch stop_watch;
uint8_t iteration = 0;

void setup() 
{
  Serial.begin(9600);
  stop_watch.start();
}

void loop() 
{
  unsigned long elapsed = stop_watch.elapsed();
  Serial.println(elapsed);

  delay(1000);
  Serial.println(stop_watch.elapsed());
  delay(1000);
  Serial.println(stop_watch.elapsed());
  Serial.println("Toggle 1:");
  stop_watch.toggle();
  delay(1000);
  Serial.println("Toggle 2:");
  Serial.println(stop_watch.elapsed());
  stop_watch.toggle();
  delay(1000);
  Serial.println(stop_watch.elapsed());
  Serial.println("Stopping:");
  stop_watch.stop();
  delay(1000);
  Serial.println(stop_watch.elapsed());

  if (++iteration % 5 == 0)
  {
    Serial.println("Resetting stop watch");
    stop_watch.reset();
    stop_watch.start();
  }
  
  // const double elapsed_sec = StopWatch::to_sec(elapsed);
  // Serial.println(elapsed_sec);
}
