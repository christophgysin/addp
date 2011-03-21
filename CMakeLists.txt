cmake_minimum_required(VERSION 2.6)
project(addp)

include(cmake/dependencies.cmake)
include(cmake/version.cmake)
include(cmake/packaging.cmake)

message("libaddp version: " ${LIBADDP_VERSION})
message("addpc version:   " ${ADDPC_VERSION})
message("addpd version:   " ${ADDPD_VERSION})

set(CMAKE_INSTALL_PREFIX /usr)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS_DEBUG -g -O0)
set(CMAKE_CXX_FLAGS_RELEASE -O2)

add_subdirectory(src)
