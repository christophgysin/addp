set(LIB addp)
file(GLOB_RECURSE SRC *.cpp)
add_library(${LIB} SHARED ${SRC})
