#ifndef TEST_H
#define TEST_H

#include <iostream>
#include <string>

inline void testResult(const std::string& actual, const std::string& expected) {
  using std::cout;
  using std::endl;

  if (actual == expected) {
    cout << "[OK] \"" << expected << "\"" << endl;
  } else {
    cout << "[ERROR] expect: \"" << expected << "\" actual: \"" << actual
         << "\"" << endl;
  }
}

#endif  // TEST_H
