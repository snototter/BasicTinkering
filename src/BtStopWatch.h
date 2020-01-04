#ifndef __BASIC_TINKERING_STOP_WATCH__
#define __BASIC_TINKERING_STOP_WATCH__

#include <Arduino.h>
/**
 * A simple toggleable stop watch.
 * * TFX = {millis or micros}
 *         a function handle
 * * TPS = how many counts (of TFX) are in a second?
 */
template<unsigned long (*TFX)(void), unsigned long TPS>
class BtStopWatch
{
public:
  // Convert result from watch.elapsed() to seconds.
  static double toSeconds(unsigned long elapsed_ticks)
  {
    return static_cast<double>(elapsed_ticks) / static_cast<double>(TPS);
  }

  BtStopWatch()
  {
    reset();
  }

  unsigned long elapsed() const 
  {
    if (is_running_)
    {
      const unsigned long e = TFX() - start_time_;
      return elapsed_ + e;
    }
    return elapsed_;
  }

  void reset()
  {
    elapsed_ = 0;
    is_running_ = false;
  }

  void start()
  {
    is_running_ = true;
    start_time_ = TFX();
  }

  void toggle()
  {
    if (is_running_)
      stop();
    else
      start();
  }

  void stop()
  {
    elapsed_ = elapsed();
    is_running_ = false;
  }

  bool isRunning() const
  {
    return is_running_;
  }

private:
  unsigned long start_time_;
  unsigned long elapsed_;     //< We accumulate elapsed time (needed because of toggle/pause)
  bool is_running_;
};

typedef BtStopWatch<millis, 1000> BtStopWatchMillis;
typedef BtStopWatch<micros, 1000000> BtStopWatchMicros;
#endif
