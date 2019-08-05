#ifndef FIXED_ERROR_BUFFER_H
#define FIXED_ERROR_BUFFER_H

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdexcept>

template <size_t N = 1024>
struct FixedErrorBuffer {
  char data[N];

#define DO_FORMAT(format, args) \
  snprintf(data, N, format, std::forward<Args>(args)...)

  template <typename... Args>
  ssize_t write(int fd, const char* format, Args&&... args) {
    int n = DO_FORMAT(format, args);
    assert(n > 0 && n < N);
    data[n] = '\n';
    return ::write(fd, data, n + 1);
  }

  template <typename... Args>
  void writeAndExit(int exitcode, int fd, const char* format, Args&&... args) {
    assert(this->write(fd, format, std::forward<Args>(args)...) >= 0);
    exit(exitcode);
  }

  template <typename Exception, typename... Args>
  void throwException(const char* format, Args&&... args) {
    assert(DO_FORMAT(format, args) > 0);
    throw Exception(data);
  }

#undef DO_FORMAT

#define THROW_EXCEPTION(T, format, args) \
  throwException<T>(format, std::forward<Args>(args)...)

  template <typename... Args>
  void throwLogicError(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::logic_error, format, args);
  }

  template <typename... Args>
  void throwInvalidArgument(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::invalid_argument, format, args);
  }

  template <typename... Args>
  void throwDomainError(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::domain_error, format, args);
  }

  template <typename... Args>
  void throwLengthError(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::length_error, format, args);
  }

  template <typename... Args>
  void throwOutOfRange(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::out_of_range, format, args);
  }

  template <typename... Args>
  void throwRuntimeError(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::runtime_error, format, args);
  }

  template <typename... Args>
  void throwRangeError(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::range_error, format, args);
  }

  template <typename... Args>
  void throwOverflowError(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::overflow_error, format, args);
  }

  template <typename... Args>
  void throwUnderflowError(const char* format, Args&&... args) {
    THROW_EXCEPTION(std::underflow_error, format, args);
  }

#undef THROW_EXCEPTION
};

#endif  // FIXED_ERROR_BUFFER_H
