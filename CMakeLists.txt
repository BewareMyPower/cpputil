cmake_minimum_required(VERSION 3.5)
project(cpputil CXX)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 11)
set(CXX_FLAGS
  -g
  -Wall
  -Wextra
  -Wno-unused-parameter
)
string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

add_subdirectory(src)
if (CMAKE_BUILD_TESTS)
    add_subdirectory(tests)
endif()
