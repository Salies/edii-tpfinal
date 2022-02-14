cmake_minimum_required(VERSION 3.21)
project(TP_Final)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXE_LINKER_FLAGS "-static")

add_executable(TP_Final main.cpp Graph.cpp Graph.h)
