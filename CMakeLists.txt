cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

project(FractalCreator)
include_directories(include)
add_executable(FractalCreator src/main.cpp src/Creator.cpp include/Creator.h include/utils.h
        include/Area.h
        include/Fractal.h src/Fractal.cpp
#        include/Renderer.h include/Controller.h include/test.h
        )

string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(FractalCreator ${SDL2_LIBRARIES})