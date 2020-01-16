#ifndef STRING_BUFFER_H
#define STRING_BUFFER_H

#include <string.h>
#include <string>
#include "string_view.h"

namespace cpputil {

// String buffer used to construct a std::string from multiple tokens with
// different type
//
// Example:
// ```c++
//   auto s = (StringBuffer{} << 1 << ", " << 3.14 << " | " << 12345678901L)
//   cout << s << endl;  // 1, 3.14, 12345678901
// ```
//
// The operator<< supports following type:
// - char
// - const char*
// - std::string
// - Numeric type that can be accepted by std::to_string() as an argument.
//
// It should be noted that if double is passed to operator<<, the converted
// string will retains 6 digits after the decimal point
class StringBuffer final {
 public:
  StringBuffer(size_t size = 1024) : initial_size_(size), buffer_(size, '\0') {}

  // Returns the internal buffer, after that the buffer will be cleared.
  // If you just want to see the internal buffer, use `view()` method.
  std::string str() {
    buffer_.resize(data_size_);
    buffer_.shrink_to_fit();

    data_size_ = 0;
    return std::move(buffer_);
  }

  cxx17::string_view view() const noexcept {
    return {buffer_.data(), data_size_};
  }

  size_t capacity() const noexcept { return buffer_.size(); }

  StringBuffer& operator<<(const char* s) { return append(s, strlen(s)); }

  StringBuffer& operator<<(const std::string& s) {
    return append(s.data(), s.size());
  }

  template <typename T>
  StringBuffer& operator<<(T x) {
    return operator<<(std::to_string(x));
  }

  StringBuffer& operator<<(char ch) {
    if (availableSize() == 0) grow(data_size_ + 1);

    buffer_[data_size_] = ch;
    data_size_++;
    return *this;
  }

 private:
  const size_t initial_size_;
  std::string buffer_;
  size_t data_size_{0};

  size_t availableSize() const noexcept { return buffer_.size() - data_size_; }

  StringBuffer& append(const char* data, size_t size) {
    if (availableSize() < size) grow(data_size_ + size);

    memcpy(&buffer_[data_size_], data, size);
    data_size_ += size;
    return *this;
  }

  void grow(size_t required_size) {
    try {
      buffer_.resize(required_size + initial_size_);
    } catch (const std::bad_alloc& e) {
      // If resize to `required_size` failed, the error is unrecoverable, so we
      // don't handle the exception.
      buffer_.resize(required_size);
    }
  }
};

}  // namespace cpputil

#endif  // STRING_BUFFER_H
