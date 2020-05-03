cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

find_package(Catch2 REQUIRED)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(FractalCreator)
include_directories(include)
add_executable(FractalCreator src/main.cpp src/Creator.cpp include/Creator.h include/utils.h
        include/Area.h src/Image.cpp include/Image.h include/Fractal.h src/Fractal.cpp src/BurningShipFractal.cpp
        include/BurningShipFractal.h src/MandelbrotSetFractal.cpp include/MandelbrotSetFractal.h)
add_executable(test tests/test.cpp)
target_link_libraries(test Catch2::Catch2)