#ifndef __BASIC_TINKERING_STOP_WATCH__
#define __BASIC_TINKERING_STOP_WATCH__

#include <Arduino.h>
/**
 * A simple toggleable stop watch.
 * Templated, so you can use either milli- or
 * microsecond-accuracy.
 * You most likely want touse the specializations
 * BtStopWatchMillis or BtStopWatchMicros.
 *
 * Template parameters:
 * ==> TFX = {millis or micros}
 *           handle to a timing function
 * ==> TPS = how many counts/ticks of TFX are in a second?
 */
template<unsigned long (*TFX)(void), unsigned long TPS>
class BtStopWatch
{
public:
  /** Convert result from watch.elapsed() to seconds. */
  static double toSeconds(unsigned long elapsed_ticks)
  {
    return static_cast<double>(elapsed_ticks) / static_cast<double>(TPS);
  }

  BtStopWatch()
  {
    reset();
  }

  /** Returns the number of ticks elapsed since this watch
   * was start()ed. */
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

  /** Start the stop watch. */
  void start()
  {
    is_running_ = true;
    start_time_ = TFX();
  }

  /** Toggle current state. */
  void toggle()
  {
    if (is_running_)
      stop();
    else
      start();
  }

  /** Stop the watch. */
  void stop()
  {
    elapsed_ = elapsed();
    is_running_ = false;
  }

  /** Returns true if stop watch is currently counting/running. */
  bool isRunning() const
  {
    return is_running_;
  }

private:
  /** Time point of last start() invocation. */
  unsigned long start_time_;
  /** Counter to accumulate elapsed time (needed for toggle). */
  unsigned long elapsed_;
  /** Flag indicating whether stop watch is currently counting. */
  bool is_running_;
};

/** Stop watch with millisecond accuracy. */
typedef BtStopWatch<millis, 1000> BtStopWatchMillis;

/** Stop watch with microsecond accuracy. */
typedef BtStopWatch<micros, 1000000> BtStopWatchMicros;
#endif
