set(TARGET consumer)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

include_directories(../src)

add_executable(test_timer test_timer.cc)
target_link_libraries(test_timer cpputil)

install(TARGETS test_timer RUNTIME DESTINATION bin)
