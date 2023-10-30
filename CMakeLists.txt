cmake_minimum_required(VERSION 3.1)
project(
  GeoFrame
  VERSION 1.0.0
  DESCRIPTION "Basic OpenGL handler."
  LANGUAGES CXX
)

add_library(
  GeoFrame STATIC
  ./src/buffer.cpp
  ./src/callback.cpp
  ./src/core.cpp
  ./src/font.cpp
  ./src/screen.cpp
  ./src/shader.cpp
  ./src/texture.cpp
  ./src/window.cpp
) 

target_include_directories(GeoFrame INTERFACE ./includes)
target_include_directories(GeoFrame PRIVATE ./resources/includes)
set_target_properties(
  GeoFrame
  PROPERTIES
  VERSION ${PROJECT_VERSION}
)

