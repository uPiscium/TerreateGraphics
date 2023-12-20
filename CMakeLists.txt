cmake_minimum_required(VERSION 3.20)
project(GeoFrame)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

add_library(
  ${PROJECT_NAME} STATIC
  impls/buffer.cpp
  impls/core.cpp
  impls/font.cpp
  impls/gl.cpp
  impls/object.cpp
  impls/screen.cpp
  impls/shader.cpp
  impls/texture.cpp
  impls/window.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ./includes)
target_include_directories(${PROJECT_NAME} PUBLIC ./includes/headers)

if(WIN32)
  target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/libs)
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)
  target_link_libraries(${PROJECT_NAME} PUBLIC freetyped)
elseif(UNIX)
  add_compile_options(-lglfw)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.0)
