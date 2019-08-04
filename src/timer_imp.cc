#include "timer_imp.h"

namespace cpputil {

void Timer::Imp::start() noexcept { before_ = Clock::now(); }

int64_t Timer::Imp::stop() const noexcept {
  using namespace std::chrono;
  auto now = Clock::now();
  return static_cast<int64_t>(
      duration_cast<microseconds>(now - before_).count());
}

}  // namespace cpputil
