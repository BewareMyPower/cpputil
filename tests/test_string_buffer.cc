#include "string_buffer.h"
using namespace cpputil;

#include "test.h"

int main(int argc, char* argv[]) {
  char buf[] = "hello";
  std::string s = "world";
  testResult((StringBuffer{} << 1 << ',' << 3.14 << ',' << 12345678901L << ':'
                             << cxx17::string_view{buf, strlen(buf)} << s)
                 .str(),
             "1,3.14,12345678901:helloworld");

  testResult((StringBuffer{} << 0.12345678), "0.123457");
  testResult((StringBuffer{} << 1.230), "1.23");
  testResult((StringBuffer{} << 1.), "1.0");
  testResult((StringBuffer{} << std::make_pair(1, "C++")), "1 => C++");
  return 0;
}
