#include "range.h"
#include "string_format.h"
using namespace cpputil;

#include <limits.h>
#include <iostream>

int main(int argc, char* argv[]) {
  auto print_range = [](Range range) {
    std::string s = "[";
    bool flag = false;
    for (int x : range) {
      appendFormatString(s, "%s%d", (flag ? ", " : ""), x);
      flag = true;
    }
    s += "]";
    std::cout << s << std::endl;
  };
  print_range({0, 4});      // [0, 1, 2, 3]
  print_range({0, -1});     // []
  print_range({0, 4, 2});   // [0, 2]
  print_range({5, 0, -2});  // [5, 3, 1]
  return 0;
}
