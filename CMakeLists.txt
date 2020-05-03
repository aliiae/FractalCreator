cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

find_package(Catch2 REQUIRED)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(FractalCreator)

add_executable(FractalCreator src/main.cpp src/FractalCreator.cpp src/FractalCreator.h src/Graphics.cpp src/Graphics.h src/utils.h src/Area.h)
add_executable(test tests/test.cpp)
target_link_libraries(test Catch2::Catch2)