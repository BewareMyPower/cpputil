#include "string_format.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

namespace cpputil {

size_t formatBufferImp(char* buf, size_t buf_size, const char* format, ...) {
  va_list args;

  va_start(args, format);
  int n = vsnprintf(buf, buf_size, format, args);
  if (n < 0) {
    fprintf(stderr, "Fatal error in formatBufferImp\n");
    abort();
  }
  va_end(args);

  return static_cast<size_t>(n);
}

}  // namespace cpputil
