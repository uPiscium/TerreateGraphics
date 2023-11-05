cmake_minimum_required(VERSION 3.10)
project(
  GeoFrame
  VERSION 1.0.0
  DESCRIPTION "Basic OpenGL handler."
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE source RELATIVE ${PROJECT_SOURCE_DIR} "src/*.cpp"})

add_library(
  GeoFrame STATIC ${source}
) 

target_include_directories(GeoFrame INTERFACE "./includes")
target_include_directories(GeoFrame PRIVATE "./resources/includes")

target_link_libraries(GeoFrame PRIVATE "./resources/libs/glfw3")
target_link_libraries(GeoFrame PRIVATE "./resources/libs/freetype")

set_target_properties(
  GeoFrame
  PROPERTIES
  VERSION ${PROJECT_VERSION}
)

