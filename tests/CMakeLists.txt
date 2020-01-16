include_directories(../src)

set(SOURCES
    test_range.cc
    test_string_buffer.cc
    test_string_format.cc
    test_string_view.cc
    test_timer.cc
)

foreach(SOURCE ${SOURCES})
    string(FIND ${SOURCE} ".cc" LENGTH)
    string(SUBSTRING ${SOURCE} 0 ${LENGTH} PROG)

    add_executable(${PROG} ${SOURCE})
    target_link_libraries(${PROG} cpputil)
    install(TARGETS ${PROG} RUNTIME DESTINATION bin)
endforeach()
