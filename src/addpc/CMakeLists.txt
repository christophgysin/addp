set(BIN addpc)
file(GLOB_RECURSE SRC *.cpp)
add_executable(${BIN} ${SRC})
target_link_libraries(${BIN}
    addp
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    )
install(TARGETS ${BIN} DESTINATION bin)
