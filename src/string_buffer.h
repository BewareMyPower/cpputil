#ifndef CPPUTIL_STRING_BUFFER_H
#define CPPUTIL_STRING_BUFFER_H

#include "string_view.h"

#include <string.h>
#include <string>
#include <utility>

namespace cpputil {

// String buffer used to construct a std::string from multiple tokens with
// different type simply.
//
// Example:
// ```c++
//  char buf[] = "hello";
//  string s0 = "world";
//  auto s = (StringBuffer{} << 1 << ',' << 3.14 << ',' << 12345678901L << ':'
//                           << cxx17::string_view{buf, strlen(buf)} << s0)
//               .str();  // 1,3.14,12345678901:helloworld
// ```
//
// The operator<< supports following type:
// - char
// - const char*
// - std::string
// - cxx17::string_view
// - Numeric type that can be accepted by std::to_string() as an argument.
//
// It should be noted that if double is passed to operator<<, the converted
// string will discard all '0' in the tail except that the double value has
// no digits after the dot. And the precesion of fixed number is 6.
// eg.
// double => string
//  0.12345678 => 0.123457
//  1.230 => 1.23
//  1.    => 1.0
class StringBuffer final {
 public:
  std::string str() const { return buffer_; }

  operator std::string() const { return str(); }

  cxx17::string_view view() const noexcept {
    return {buffer_.data(), buffer_.size()};
  }

  std::string detach() { return std::move(buffer_); }

  void clear() { buffer_.clear(); }

  size_t capacity() const noexcept { return buffer_.size(); }

  StringBuffer& operator<<(const char* s) {
    buffer_ += (s ? s : "");
    return *this;
  }

  StringBuffer& operator<<(const std::string& s) {
    buffer_ += s;
    return *this;
  }

  StringBuffer& operator<<(char ch) {
    buffer_ += ch;
    return *this;
  }

  StringBuffer& operator<<(cxx17::string_view view) {
    buffer_.append(view.data(), view.size());
    return *this;
  }

  StringBuffer& operator<<(double x) {
    auto s = std::to_string(x);
    s.erase(s.find_last_not_of('0') + 1);
    if (s.back() == '.') s += '0';

    buffer_ += s;
    return *this;
  }

  template <typename T>
  StringBuffer& operator<<(T x) {
    buffer_ += std::to_string(x);
    return *this;
  }

  template <typename First, typename Second>
  StringBuffer& operator<<(const std::pair<First, Second>& x) {
    return (*this) << x.first << " => " << x.second;
  }

 private:
  std::string buffer_;
};

}  // namespace cpputil

#endif  // CPPUTIL_STRING_BUFFER_H
