set(SOURCES
    timer.cc
    timer_imp.cc
)
set(HEADERS
    string_view.h
    timer.h
)

add_library(cpputil ${SOURCES})

install(TARGETS cpputil DESTINATION lib)
install(FILES ${HEADERS} DESTINATION include)
