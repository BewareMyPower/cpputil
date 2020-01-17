#include "string_buffer.h"
using namespace cpputil;

#include <iostream>
using namespace std;

void testResult(const string& actual, const string& expected) {
  if (actual == expected) {
    cout << "[OK] " << expected << endl;
  } else {
    cout << "[ERROR] expect: \"" << expected << "\" actual: \"" << actual
         << "\"" << endl;
  }
}

int main(int argc, char* argv[]) {
  char buf[] = "hello";
  string s = "world";
  testResult((StringBuffer{} << 1 << ',' << 3.14 << ',' << 12345678901L << ':'
                             << cxx17::string_view{buf, strlen(buf)} << s)
                 .str(),
             "1,3.14,12345678901:helloworld");

  testResult((StringBuffer{} << 0.12345678), "0.123457");
  testResult((StringBuffer{} << 1.230), "1.23");
  testResult((StringBuffer{} << 1.), "1.0");
  return 0;
}
