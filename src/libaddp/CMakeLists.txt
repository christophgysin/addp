set(LIB addp)
file(GLOB_RECURSE HDR *.h)
file(GLOB_RECURSE SRC *.cpp)
add_library(${LIB} SHARED ${SRC})
target_link_libraries(${LIB}
    ${Boost_SYSTEM_LIBRARY}
    ${Boost_PROGRAM_OPTIONS_LIBRARY}
    )
set_target_properties(${LIB} PROPERTIES
    VERSION ${ADDP_VERSION}
    SOVERSION ${ADDP_VERSION}
    )
install(TARGETS ${LIB} DESTINATION lib)
install(FILES ${HDR} DESTINATION include/${LIB})
