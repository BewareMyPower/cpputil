## cpputil

A Linux util library based on C++11.

## How to use

This project also show a simple usage of cmake, the struct of this project is:

```
$ tree . -L 1
.
├── build.sh
├── CMakeLists.txt
├── tests            // Unit tests which use cpputil library.
├── README.md
└── src              // Sources of cpputil library.
```

You can build the library simply by run `./build.sh`, and following directories will be added:

```
bin     // Installed executable binaries.
include // Installed header files. 
lib     // Installed libraries. For now, it's just *libcpputil.a* .
```

You can modify `CMAKE_INSTALL_PREFIX` in [build.sh](./build.sh) to change **INSTALL_PATH**, it's default in current directory.

After that, you can imitate [tests/CMakeLists.txt](./tests/CMakeLists.txt) to write your own CMakeLists.txt to use cpputil, or simply write a Makefile. If your project has only one file (eg. `myproject.cc`), use g++ directly, for example:

```
g++ myproject.cc -std=c++11 -I <INSTALL_PATH>/include -L <INSTALL_PATH>/lib/libcpputil.a
```

Run `./build.sh clean` to remove `build` directory, `./build uninstall` to remove `include`, `lib`, `bin`.

## TODO

1. Use test framework (like [GoogleTest](https://github.com/google/googletest)) to write unit tests.
2. Build shared library instead of static library.
