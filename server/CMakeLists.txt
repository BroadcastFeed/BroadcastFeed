cmake_minimum_required(VERSION 3.16.3)
project(server)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pthread")

file(GLOB SOURCES src/*.cpp src/*/*.cpp)

add_executable(server src/main.cpp ${SOURCES})

