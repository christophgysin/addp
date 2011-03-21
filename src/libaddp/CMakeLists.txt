set(LIB addp)
file(GLOB_RECURSE SRC *.cpp)
add_library(${LIB} SHARED ${SRC})
target_link_libraries(${LIB}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    )
