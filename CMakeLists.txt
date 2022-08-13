cmake_minimum_required(VERSION 3.20)
project(factor)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/include")
link_directories(/usr/local/lib)

add_executable(factor main.cpp Factorer.cpp Factorer.h)
target_link_libraries(factor -lgmpxx -lgmp)
