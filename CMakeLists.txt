cmake_minimum_required(VERSION 3.8)
project(problem1_Localization)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES main.cpp Plane.cpp Plane.h Parameters.h)
add_executable(problem1_Localization ${SOURCE_FILES})