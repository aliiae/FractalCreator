cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(FractalCreator)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src include)

add_executable(FractalCreator src/main.cpp include/Area.h
        include/utils.h src/utils.cpp
        src/Creator.cpp include/Creator.h
        include/Fractal.h src/Fractal.cpp
        include/MandelbrotSet.h src/MandelbrotSet.cpp
        include/BurningShip.h src/BurningShip.cpp
        include/Controller.h src/Controller.cpp
        src/Renderer.cpp include/Renderer.h)

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(FractalCreator ${SDL2_LIBRARIES})