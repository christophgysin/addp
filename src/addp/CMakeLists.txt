set(LIB addp)
file(GLOB_RECURSE SRC *.cpp)

add_library(${LIB} SHARED ${SRC})
target_link_libraries(${LIB}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_FILESYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    pthread
    )
set_target_properties(${LIB} PROPERTIES
    VERSION ${ADDP_VERSION}
    SOVERSION ${ADDP_VERSION}
    )

install(TARGETS ${LIB}
    DESTINATION lib)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    DESTINATION include
    FILES_MATCHING PATTERN "*.h")
