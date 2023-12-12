cmake_minimum_required(VERSION 3.6)
project(cf)

set(CMAKE_CXX_STANDARD 17)

include_directories(/Library/Developer/CommandLineTools/usr/include)
add_executable(cf main.cpp)
set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -Wextra -Wconversion -fstandalone-debug -D_GLIBCXX_DEBUG")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}" )