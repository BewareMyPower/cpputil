#include "timer.h"

#include <string.h>

#include <chrono>
#include <iostream>
#include <string>
#include <thread>
using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 2 || strcmp(argv[1], "-h") == 0 ||
      strcmp(argv[1], "--help") == 0) {
    cerr << "Usage: " << argv[0] << " timeout_us" << endl;
    return 1;
  }

  auto timeout_us = static_cast<int64_t>(stoll(argv[1]));
  cout << "Sleep for " << timeout_us << " microseconds..." << endl;

  cpputil::Timer timer;
  timer.start();
  this_thread::sleep_for(chrono::microseconds(timeout_us));
  auto t = timer.stop();

  cout << "Waked up after " << t << " microseconds" << endl;
  return 0;
}
