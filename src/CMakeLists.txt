set(SOURCES
    timer.cc
    timer_imp.cc
)
set(HEADERS
    char_sequence.h
    timer.h
)

add_library(cpputil ${SOURCES})

install(TARGETS cpputil LIBRARY DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
