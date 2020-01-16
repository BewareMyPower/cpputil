set(SOURCES
    string_format.cc
    timer.cc
    timer_imp.cc
)
set(HEADERS
    range.h
    string_buffer.h
    string_format.h
    string_view.h
    timer.h
)

add_library(cpputil ${SOURCES})

install(TARGETS cpputil DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include/cpputil)
