#ifndef CPPUTIL_STRING_FORMAT_H
#define CPPUTIL_STRING_FORMAT_H

#include <assert.h>
#include <string>

namespace cpputil {

/**
 * @brief Simple wrapper of snprintf(3), excepted that if snprintf(3) returns
 * negative value, this function will terminates the program.
 */
size_t formatBufferImp(char* buf, size_t buf_size, const char* format, ...);

/**
 * @brief Format \p buf with given C-style \p format and \p args.
 *
 * @return Number of characters printed (excluding terminated '\0').
 */
template <typename... Args>
inline size_t formatBuffer(char* buf, size_t buf_size, const char* format,
                           Args&&... args) {
  return formatBufferImp(buf, buf_size, format, std::forward<Args>(args)...);
}

/**
 * @brief Format \p s with given C-style \p format and \p args.
 *
 * @sa formatBuffer()
 */
template <typename... Args>
inline size_t formatString(std::string& s, const char* format, Args&&... args) {
  // C++11 ensures that string must be terminated with '\0'
  return formatBuffer(&s[0], s.size() + 1, format, std::forward<Args>(args)...);
}

/**
 * @brief Create a formatted string with C-style \p format and \p args.
 */
template <typename... Args>
inline std::string makeFormatString(const char* format, Args&&... args) {
  size_t size =
      formatBufferImp(nullptr, 0, format, std::forward<Args>(args)...);
  std::string s(size, '\0');
  assert(formatString(s, format, std::forward<Args>(args)...) == size);
  return s;
}

/**
 * @brief Append formatted string with C-style \p format and \p args  to \p s.
 */
template <typename... Args>
inline void appendFormatString(std::string& s, const char* format,
                               Args&&... args) {
  s += makeFormatString(format, std::forward<Args>(args)...);
}

}  // namespace cpputil

#endif  // CPPUTIL_STRING_FORMAT_H
