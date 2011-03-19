cmake_minimum_required(VERSION 2.6)
project(addp)

include(FindBoost)
find_package(Boost REQUIRED system program_options)

set(CMAKE_INSTALL_PREFIX /usr)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_FLAGS -Wall)
set(CMAKE_CXX_FLAGS_DEBUG -g -O0)
set(CMAKE_CXX_FLAGS_RELEASE -O2)

add_subdirectory(src)
