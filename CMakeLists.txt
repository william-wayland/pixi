﻿# CMakeList.txt : CMake project for pixi, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 20)

project ("pixi")

# Add source to this project's executable.
add_executable (pixi "pixi.cpp" "Context.cpp" "Menu.cpp" "Stacker.cpp" "Snake.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET pixi PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
