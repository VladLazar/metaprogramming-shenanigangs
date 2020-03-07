cmake_minimum_required(VERSION 3.10)
project(assignment1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -g")

add_executable(part1 part1.cpp)
add_executable(part2 part2.cpp)
add_executable(part3 part3.cpp)
