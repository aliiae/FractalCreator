cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(FractalCreator)
include_directories(include)
add_executable(FractalCreator src/main.cpp src/Creator.cpp include/Creator.h include/utils.h
        include/Area.h src/Image.cpp include/Image.h
        include/Fractal.h src/Fractal.cpp src/BurningShip.cpp include/BurningShip.h src/MandelbrotSet.cpp include/MandelbrotSet.h)