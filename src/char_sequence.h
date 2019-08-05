#ifndef CHAR_SEQUENCE_H
#define CHAR_SEQUENCE_H

#include <string.h>

// Simple imitation of string_view<char> in C++17.
class CharSequence {
 public:
  static constexpr size_t npos = size_t(-1);
  CharSequence() noexcept = default;
  CharSequence(const char* ptr, size_t size) noexcept
      : data_(ptr), size_(size) {}
  CharSequence(const CharSequence&) = default;
  CharSequence(const char* str) noexcept : CharSequence(str, strlen(str)) {}

  CharSequence& operator=(const CharSequence&) = default;

  const char* cbegin() const noexcept { return data(); }
  const char* begin() const noexcept { return cbegin(); }

  const char* cend() const noexcept { return data() + size(); }
  const char* end() const noexcept { return cend(); }

  // Without bounds checking.
  const char& operator[](size_t pos) const noexcept { return data_[pos]; }

  // With bounds checking, may throw std::out_of_range
  const char& at(size_t pos) const;

  const char& front() const noexcept { return (*this)[0]; }
  const char& back() const noexcept { return (*this)[size() - 1]; }
  const char* data() const noexcept { return data_; }
  size_t size() const noexcept { return size_; }
  size_t length() const noexcept { return size(); }
  bool empty() const noexcept { return size() == 0; }

  void remove_prefix(size_t n);
  void remove_suffix(size_t n);

  void swap(CharSequence& v) noexcept;

  size_t copy(char* dest, size_t count, size_t pos = 0) const;

  // With bounds checking, may throw std::out_of_range
  CharSequence substr(size_t pos = 0, size_t count = npos) const;

  // TODO: compare(), find() series, operator==,<,>,<=,>=,<<

 private:
  const char* data_ = nullptr;
  size_t size_ = 0;

  void rangeCheck(size_t pos) const;
};

#include <assert.h>
#include <algorithm>
#include "fixed_error_buffer.h"

inline const char& CharSequence::at(size_t pos) const {
  if (pos >= size()) {
    FixedErrorBuffer<128>().throwOutOfRange(
        "CharSequence::at: pos (which is %zd) >= this->size() (which is %zd)",
        pos, size());
  }
  return (*this)[pos];
}

inline void CharSequence::swap(CharSequence& v) noexcept {
  std::swap(data_, v.data_);
  std::swap(size_, v.size_);
}

size_t CharSequence::copy(char* dest, size_t count, size_t pos) const {
  return std::distance(
      dest,
      std::copy(cbegin(), cbegin() + std::min(count, size() - pos), dest));
}

inline CharSequence CharSequence::substr(size_t pos, size_t count) const {
  if (pos >= size()) {
    FixedErrorBuffer<128>().throwOutOfRange(
        "CharSequence::substr: pos (which is %zd) >= this->size() (which is "
        "%zd)",
        pos, size());
  }
  return {data() + pos, std::min(count, size() - pos)};
}

inline void CharSequence::remove_prefix(size_t n) {
  assert(n <= size());
  data_ += n;
  size_ -= n;
}

inline void CharSequence::remove_suffix(size_t n) {
  assert(n <= size());
  data_ += n;
  size_ -= n;
}

#endif  // CHAR_SEQUENCE_H
