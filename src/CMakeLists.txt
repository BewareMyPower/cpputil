set(SOURCES
    timer.cc
    timer_imp.cc
)
set(HEADERS
    char_sequence.h
    fixed_error_buffer.h
    timer.h
)

add_library(cpputil ${SOURCES})

install(TARGETS cpputil DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
