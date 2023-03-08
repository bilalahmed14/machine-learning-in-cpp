cmake_minimum_required(VERSION 3.14)
project(machine-learning-in-cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

file(GLOB SOURCES "src/*.cpp")

add_executable(ML_in_cpp main.cpp ${SOURCES})