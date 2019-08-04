#include "timer.h"
#include "timer_imp.h"

#include <assert.h>

namespace cpputil {

Timer::Timer() {
  imp_.reset(new Timer::Imp());
  assert(imp_);
}

Timer::~Timer() = default;

Timer::Timer(Timer&&) noexcept = default;
Timer& Timer::operator=(Timer&&) noexcept = default;

void Timer::start() const noexcept { imp_->start(); }

int64_t Timer::stop() const noexcept { return imp_->stop(); }

}  // namespace cpputil
