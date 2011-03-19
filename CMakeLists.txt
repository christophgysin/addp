cmake_minimum_required(VERSION 2.6)
project(addp)

add_subdirectory(src)

include(FindBoost)
find_package(Boost REQUIRED system program_options)

set(CMAKE_INSTALL_PREFIX /usr)
