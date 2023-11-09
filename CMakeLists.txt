cmake_minimum_required(VERSION 3.10)
project(
  GeoFrame
  VERSION 1.0.0
  DESCRIPTION "Basic OpenGL handler."
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

file(
  GLOB_RECURSE
  source
  RELATIVE
  ${PROJECT_SOURCE_DIR}
  "src/*.cpp"
)

add_library(
  GeoFrame
  SHARED
  ${source}
)

target_include_directories(GeoFrame PUBLIC "includes")

target_link_libraries(GeoFrame PRIVATE "../libs/glfw3")
target_link_libraries(GeoFrame PRIVATE "../libs/freetyped")

set_target_properties(
  GeoFrame
  PROPERTIES
  VERSION ${PROJECT_VERSION}
)

