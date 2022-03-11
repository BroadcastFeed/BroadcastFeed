cmake_minimum_required(VERSION 3.16.3)
project(server)

#list(APPEND CMAKE_CXX_FLAGS "-pthread -std=c++11 ${CMAKE_CXX_FLAGS}")
set(CMAKE_CXX_STANDARD 20)

file(GLOB SOURCES src/*.cpp src/*/*.cpp)

add_executable(server src/main.cpp ${SOURCES})

target_link_libraries(server pthread)
#target_link_libraries(server -std=c++0x -pthread)
