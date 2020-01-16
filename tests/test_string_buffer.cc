#include "string_buffer.h"
using namespace cpputil;

#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
  StringBuffer buffer(10);
  auto dump = [&buffer] {
    auto view = buffer.view();
    cout << view.size() << " of " << buffer.capacity() << " | " << '"'
         << string(view.data(), view.size()) << '"' << endl;
  };
  buffer << "hello";
  dump();  // 5 of 10 | "hello"
  buffer << 123456;
  dump();  // 11 of 21 | "hello123456"
  buffer << 3.14;
  dump();  // 19 of 21 | "hello1234563.140000"
  buffer << '|' << -1234;
  dump();                        // 25 of 35 | "hello1234563.140000|-1234"
  cout << buffer.str() << endl;  // hello1234563.140000|-1234
  dump();                        // 0 of 0 | ""
  return 0;
}
