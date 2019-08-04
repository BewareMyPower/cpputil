#ifndef TIMER_IMP_H
#define TIMER_IMP_H

#include "timer.h"

#include <chrono>

namespace cpputil {

class Timer::Imp final {
 public:
  using Clock = std::chrono::high_resolution_clock;
  using TimePoint = Clock::time_point;
  using Duration = std::chrono::duration<std::chrono::microseconds>;

  void start() noexcept;
  int64_t stop() const noexcept;

 private:
  TimePoint before_;
};

}  // namespace cpputil

#endif  // TIMER_IMP_H
