#ifndef CPPUTIL_TIMER_H
#define CPPUTIL_TIMER_H

#include <memory>

namespace cpputil {


// Timer is used to count time between two time points.
// Example:
//   Timer timer;  // starts at UTC epoch (1970-01-01 00:00:00)
//   timer.start();
//   // Do something...
//   uint64_t n = timer.stop();  // n microseconds between start() and stop().
class Timer final {
 public:
  Timer();
  ~Timer();

  Timer(Timer&&) noexcept;
  Timer& operator=(Timer&&) noexcept;

  void start() const noexcept;

  // Returns the number of microseconds between now and last time start() was called.
  int64_t stop() const noexcept;

 private:
  class Imp;
  std::unique_ptr<Imp> imp_;
};

}  // namespace cpputil

#endif  // CPPUTIL_TIMER_H
