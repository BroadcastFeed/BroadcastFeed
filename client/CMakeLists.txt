cmake_minimum_required(VERSION 3.16.3)
project(client)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-pthread")

file(GLOB SOURCES src/*.cpp)

add_executable(client src/main.cpp ${SOURCES} src/Tokenizer.h)
