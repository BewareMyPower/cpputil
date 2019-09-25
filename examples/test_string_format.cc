#include "string_format.h"
using namespace cpputil;
using std::string;

#include <stdio.h>

inline void CheckResult(const string& result, const string& expected) {
  if (result == expected) {
    printf("[OK] \"%s\"\n", result.data());
  } else {
    fprintf(stderr, "[FAILED] result is \"%s\" but expect \"%s\"\n",
            result.data(), expected.data());
  }
}

inline void CheckResult(size_t result, size_t expected) {
  if (result == expected) {
    printf("[OK] %zu\n", result);
  } else {
    fprintf(stderr, "[FAILED] result is %zu but expect %zu\n", result,
            expected);
  }
}

int main(int argc, char* argv[]) {
  auto s = makeFormatString("%02x,%.3f,%s", 0x12, 3.1415926, "xyz");
  CheckResult(s, "12,3.142,xyz");

  s.resize(3);
  CheckResult(formatString(s, "%.*s", 7, "1234567"), 7);
  CheckResult(s, "123");

  appendFormatString(s, "%d", 4567);
  CheckResult(s, "1234567");
  return 0;
}
