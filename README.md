## cpputil

A Linux util library based on C++11.

## How to install

Install **cpputil** to `<INSTALL_PATH>` (default: `./cpputil`):

```bash
./build.sh -i <INSTALL_PATH>
```

If you want to build test binaries, add options `--with-tests`.

Uninstall **cpputil** under `<DIR>`:

```bash
./build.sh -u <DIR>
```

Run `./build.sh -h` to see more details.

## How to use

Assuming `<INSTALL_DIR>/include` has been added to your include path.

### 1. `Timer`

```c++
#include "cpputil/timer.h"
```

Compute the microseconds between two time point

```c++
cpputil::Timer timer;
timer.start();
// TODO: do something here
auto time_us = timer.stop();  // the microseconds between start() and stop()
```

### 2. string formatter functions

```c++
#include "cpputil/string_format.h"
```

Use C-Style format to construct a string or append the formatted string to an existed string.

```c++
auto s = cpputil::makeFormatString("%d: %s", 1, "xyz");  // "1: xyz"
cpputil::appendFormatString(s, " | %.3lf", 3.14);  // s is now "1: xyz | 3.140"
```

It may be **deprecated** because it's just a simple wrapper of `snprintf`, [fmt](https://github.com/fmtlib/fmt) may be the better option.

If your compiler supports C++ 20, use [format](https://en.cppreference.com/w/cpp/utility/format/format).

### 3. `Range`

```
#include "cpputil/range.h"
```

Just like Python's `range` to replace plain `for` loop.

The `Range` class has only one constructor:

```c++
Range(int start, int end, int step = 1)
```

And it's copyable and moveable, though it's meaningless because we usually use `Range` in a loop, like following cases:

```c++
for (int i : Range(0, 10))  // for (int i = 0; i < 10; i++)
```

```c++
for (int i : Range(0, 10, 2))  // for (int i = 0; i < 10; i += 2)
```

```c++
for (int i : Range(10, 0))  // for (int i = 10; i > 0; i--)
```

```c++
for (int i : Range(10, 0, -2))  // for (int i = 10; i > 0; i -= 2)
```

`step` must be non-zero, otherwise it will throw a `std::runtime_error`.

It's far not as strong as C++ 20's [range](https://en.cppreference.com/w/cpp/ranges), but it's simple and can avoid some stupid error when use plain `for` loop, like:

```c++
for (int i = N; i > 0; i++)  // infinite loop
```

It's too often to write `i++` in my coding experience.

### 4. `StringBuffer`

```c++
#include "cpputil/string_buffer.h"
```

It's used to construct a `std::string` by simply concat some elements

```c++
char buf[] = " | ";
auto s = (cpputil::StringBuffer{} << '^'   // char
                                  << 1     // int
                                  << ": "  // const char*
                                  << 3.14  // double
                                  // use string_view to wrap C-Style buffer
                                  << cpputil::cxx17::string_view{buf, strlen(buf)}
                                  << make_pair("cpputil", 0)).detach();
// now, s is "^1: 3.14 | cpputil => 0"
```

It should be noted that we use `detach()` method here, it move the internal `std::string` as the returned value to **avoid meaningless copy of string**, which means that the `StringBuffer` is no longer valid.

If you just want to get a copy or view of internal string , call `str()` or `view()`. It can be implicitly converted to `std::string`, eg:

```c++
cpputil::StringBuffer buffer{};
buffer << "hello world!";

auto print_string = [](const std::string& s) { std::cout << s << std::endl; };
print_string(buffer);  // call buffer.str() to get a copy of internal string
```

It looks like `std::stringstream`, but it doesn't have control on format like `std::precision`, when passing floating numbers to `operator<<`, it discards all `'0'` in the tail, if there is no digit after the dot, add one. Limited by default `std::to_string`, the precision of floating numbers is 6.

| double     | string   |
| ---------- | -------- |
| 0.12345678 | 0.123457 |
| 1.230      | 1.23     |
| 1.         | 1.0      |

Instead, it can serialize `std::pair` and `string_view`. The `string_view` is a toy implementation of [C++17's `string_view`](https://en.cppreference.com/w/cpp/string/basic_string_view), if you're using C++17, just`using std::string_view` instead of `using cpputil::cxx17::string_view`.

### 5. Container

```c++
#include "cpputil/container.h"
```

It uses `cpputil::StringBuffer` to serialize STL container to `std::string`, like Scala's `mkString` methods. But it's not easy to add methods to existed classes in C++, it's easy to that in Scala by `implicit`, and even easier in Ruby.

Giving the `vector` and `map`  instances as the example of sequence container and associate container

```c++
std::vector<int> v{1, 2, 3};
std::map<int, int> m{{1, "Foo"}, {3, "Bar"}};
```

Use `Container` to call `makeString`:

```c++
auto seq_container = cpputil::toContainer(v);
auto map_container = cpputil::toContainer(m);
```

Now, `seq_container.makeString()` is `[1, 2, 3]`, and `map_container.makeString()` is `{1 => Foo, 3 => Bar}`.

You can just call `cpputil::toContainer(v).mkString()` without constructing a `Container` instance.

You can specify the seperator (default `", "` ) or begin/end string (default `"["`/`"]"` for sequence container and `"{"`/`"}"` for associate container), see `container.h`:

```c++
std::string makeString() const { return makeString(", "); }

std::string makeString(const char* separator);

std::string makeString(const char* start, const char* separator,                                                const char* end) const;
```

We may provide more methods to `Container` in the future.

See examples in [tests](tests/) or installed headers for more information.
