cmake_minimum_required(VERSION 2.8)

if(${IWYU})
include(cmake/iwyu.cmake)
endif()

project(addp)

include(cmake/dependencies.cmake)
include(cmake/version.cmake)
include(cmake/packaging.cmake)
include(cmake/testing.cmake)

message("addp version: " ${ADDP_VERSION})

set(CMAKE_INSTALL_PREFIX /usr)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG -g -O0)
set(CMAKE_CXX_FLAGS_RELEASE -O2)

add_subdirectory(src)
