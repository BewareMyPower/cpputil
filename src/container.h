#ifndef STRING_CONTAINER_H
#define STRING_CONTAINER_H

#include "string_buffer.h"

namespace cpputil {

// Wrapper of STL container (as template argument `T`) to provide util methods
template <typename T>
class Container {
  template <typename U>
  struct IsPair {
    static constexpr bool value = false;
  };

  template <typename First, typename Second>
  struct IsPair<std::pair<First, Second>> {
    static constexpr bool value = true;
  };

 public:
  static constexpr bool isAssociate() {
    return IsPair<typename T::value_type>::value;
  }

  Container(const T& c) noexcept : c_(c) {}

  std::string makeString() const { return makeString(", "); }

  std::string makeString(const char* separator) const {
    const char* begin = isAssociate() ? "{" : "[";
    const char* end = isAssociate() ? "}" : "]";
    return makeString(begin, separator, end);
  }

  std::string makeString(const char* start, const char* separator,
                         const char* end) const;

 private:
  const T& c_;
};

template <typename T>
inline Container<T> toContainer(const T& t) noexcept {
  return Container<T>(t);
}

template <typename T>
inline std::string Container<T>::makeString(const char* start,
                                            const char* separator,
                                            const char* end) const {
  StringBuffer buffer;
  buffer << start;

  bool not_first = false;
  for (const auto& x : c_) {
    if (not_first) {
      buffer << separator;
    } else {
      not_first = true;
    }
    buffer << x;
  }

  buffer << end;
  return buffer.detach();
}

}  // namespace cpputil

#endif  // STRING_CONTAINER_H
