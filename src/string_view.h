#ifndef CPPUTIL_STRING_VIEW_H
#define CPPUTIL_STRING_VIEW_H

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
  constexpr string_view(const char* ptr, size_t size)
      : data_(ptr), size_(size) {}
  constexpr string_view(const char* s) : string_view(s, strlen(s)) {}

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

  int compare(string_view v) const noexcept {
    return memcmp(data(), v.data(), size());
  }
  int compare(size_t pos1, size_t count1, string_view v) const {
    return substr(pos1, count1).compare(v);
  }
  int compare(size_t pos1, size_t count1, string_view v, size_t pos2,
              size_t count2) const {
    return substr(pos1, count1).compare(v.substr(pos2, count2));
  }
  int compare(const char* s) const { return compare(string_view(s)); }
  int compare(size_t pos1, size_t count1, const char* s) const {
    return substr(pos1, count1).compare(s);
  }
  int compare(size_t pos1, size_t count1, const char* s, size_t count2) const {
    return substr(pos1, count1).compare(string_view(s, count2));
  }

  // NOTE: find() methods in C++17 are  functions
  size_t find(string_view v, size_t pos = 0) const noexcept {
    return std::distance(
        cbegin(), std::search(cbegin() + pos, cend(), v.cbegin(), v.cend()));
  }
  size_t find(char ch, size_t pos = 0) const noexcept {
    return find(string_view(std::addressof(ch), 1), pos);
  }
  size_t find(const char* s, size_t pos, size_t count) const {
    return find(string_view(s, count), pos);
  }
  size_t find(const char* s, size_t pos = 0) const {
    return find(string_view(s), pos);
  }

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

inline bool operator==(string_view lhs, string_view rhs) noexcept {
  return lhs.compare(rhs) == 0;
}

inline bool operator!=(string_view lhs, string_view rhs) noexcept {
  return lhs.compare(rhs) != 0;
}

inline bool operator<(string_view lhs, string_view rhs) noexcept {
  return lhs.compare(rhs) < 0;
}

inline bool operator<=(string_view lhs, string_view rhs) noexcept {
  return lhs.compare(rhs) <= 0;
}

inline bool operator>(string_view lhs, string_view rhs) noexcept {
  return lhs.compare(rhs) > 0;
}

inline bool operator>=(string_view lhs, string_view rhs) noexcept {
  return lhs.compare(rhs) >= 0;
}

// TODO: Implement it with std::ostream::sentry

}  // namespace cxx17

}  // namespace cpputil

#endif  // CPPUTIL_STRING_VIEW_H
