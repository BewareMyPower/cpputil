#ifndef CHAR_SEQUENCE_H
#define CHAR_SEQUENCE_H

#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <stdexcept>

namespace cpputil {

// Simple implementation of string_view in C++17
namespace cxx17 {

class string_view {
 public:
  static constexpr size_t npos = size_t(-1);
  constexpr string_view() noexcept = default;
  constexpr string_view(const string_view&) = default;
  constexpr string_view(const char* ptr, size_t size) noexcept : data_(ptr),
                                                                 size_(size) {}
  constexpr string_view(const char* s) noexcept : string_view(s, strlen(s)) {}

  string_view& operator=(const string_view&) = default;

  constexpr const char* cbegin() const noexcept { return data(); }
  constexpr const char* begin() const noexcept { return cbegin(); }

  constexpr const char* cend() const noexcept { return data() + size(); }
  constexpr const char* end() const noexcept { return cend(); }

  // Without bounds checking.
  constexpr const char& operator[](size_t pos) const noexcept {
    return data_[pos];
  }

  // With bounds checking, may throw std::out_of_range
  constexpr const char& at(size_t pos) const {
    return (pos < size()) ? (*this)[pos]
                          : (throwOutOfRange("at", pos), (*this)[0]);
  }

  constexpr const char& front() const noexcept { return (*this)[0]; }
  constexpr const char& back() const noexcept { return (*this)[size() - 1]; }
  constexpr const char* data() const noexcept { return data_; }
  constexpr size_t size() const noexcept { return size_; }
  constexpr size_t length() const noexcept { return size(); }
  constexpr bool empty() const noexcept { return size() == 0; }

  // NOTE: remove_prefix, remove_suffix, swap are constexpr methods in C++17
  void remove_prefix(size_t n) {
    assert(n <= size());
    data_ += n;
    size_ -= n;
  }

  void remove_suffix(size_t n) {
    assert(n <= size());
    size_ -= n;
  }

  void swap(string_view& v) noexcept {
    std::swap(data_, v.data_);
    std::swap(size_, v.size_);
  }

  size_t copy(char* dest, size_t count, size_t pos = 0) const {
    return std::distance(
        dest,
        std::copy(cbegin(), cbegin() + std::min(count, size() - pos), dest));
  }

  // With bounds checking, may throw std::out_of_range
  string_view substr(size_t pos = 0, size_t count = npos) const {
    return (pos < size())
               ? string_view{data() + pos, std::min(count, size() - pos)}
               : (throwOutOfRange("substr", pos), *this);
  }

  // TODO: compare(), find() series, operator==,<,>,<=,>=,<<

 private:
  const char* data_ = nullptr;
  size_t size_ = 0;

  void throwOutOfRange(const char* method, size_t pos) const {
    char buf[128];
    (void)snprintf(
        buf, sizeof buf,
        "string_view::%s: pos (which is %zu) >= this->size() (which is %zu)",
        method, pos, size());
    throw std::out_of_range(buf);
  }
};

}  // namespace cpputil::cxx17

}  // namespace cpputil

#endif  // CHAR_SEQUENCE_H
