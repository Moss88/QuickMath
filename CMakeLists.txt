cmake_minimum_required(VERSION 2.8)
include(ExternalProject)
project(QuickMath)
include_directories(include)
include_directories(picosat)

add_subdirectory(gtest-1.7.0)
add_subdirectory(picosat)
add_subdirectory(src)
add_subdirectory(tests)

