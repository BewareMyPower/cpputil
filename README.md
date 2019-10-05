## cpputil

A Linux util library based on C++11.

## How to use

Install **cpputil** to `<INSTALL_PATH>`:

```bash
./build.sh -i <INSTALL_PATH>
```

If you want to build test binaries, add options `--with-tests`.

Uninstall **cpputil** under `<DIR>`:

```bash
./build.sh -u <DIR>
```

Run `./build.sh -h` to see more details.

See examples in [tests](tests/) or installed headers to learn how to use.

## TODO

1. Use test framework (like [GoogleTest](https://github.com/google/googletest)) to write unit tests.
2. Build shared library instead of static library.
