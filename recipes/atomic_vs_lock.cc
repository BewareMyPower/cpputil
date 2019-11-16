// g++ atomic_vs_lock.cc ./cpputil/lib/libcpputil.a -std=c++11 -pthread
// -I./cpputil/include
#include <stdio.h>
#include <atomic>
#include <mutex>
#include <thread>
#include "cpputil/timer.h"

class SynchronizedInteger {
 public:
  SynchronizedInteger(int data = 0) : data_(data) {}

  operator int() const noexcept { return data_; }

  int operator++(int) {
    std::unique_lock<std::mutex> lock(mutex_);
    int data = data_;
    data_++;
    lock.unlock();
    return data;
  }

 private:
  int data_;
  mutable std::mutex mutex_;
};

constexpr int kThreadCount = 4;
constexpr int kLoopCount = 1000000;
static cpputil::Timer kTimer;
static std::thread kThreads[kThreadCount];

template <typename Integer>
void threadFunc(Integer& value) {
  for (int i = 0; i < kLoopCount; i++) value++;
}

template <typename Integer>
static void testGetAndIncrement() {
  Integer integer{0};

  kTimer.start();
  for (auto& thread : kThreads)
    thread = std::move(std::thread{threadFunc<Integer>, std::ref(integer)});
  for (auto& thread : kThreads) thread.join();

  printf("time: %lfms, value=%d\n", kTimer.stop() / 1000.0,
         static_cast<int>(integer));
}

int main(int argc, char* argv[]) {
  testGetAndIncrement<int>();
  testGetAndIncrement<SynchronizedInteger>();
  testGetAndIncrement<std::atomic_int>();
  return 0;
}
