cmake_minimum_required(VERSION 3.19)
project(opengl_learning)

set(CMAKE_CXX_STANDARD 20)

link_directories(lib)

include_directories(include)

add_definitions(-DWIN32 -D_WINDOWS)

add_executable(opengl_learning WIN32 main.cpp Shader.h Shader.cpp)

target_link_libraries(opengl_learning sb7_d.lib glfw3_d.lib opengl32.lib glu32.lib)
