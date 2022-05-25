cmake_minimum_required(VERSION 3.20)
project(factor)

set(CMAKE_CXX_STANDARD 17)

add_executable(factor main.cpp Factorer.cpp Factorer.h)
