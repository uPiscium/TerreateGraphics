cmake_minimum_required(VERSION 3.20)
project(GeoFrame)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

add_library(
  ${PROJECT_NAME} STATIC
  buffer.cpp
  core.cpp
  defines.cpp
  event.cpp
  font.cpp
  gl.cpp
  job.cpp
  network.cpp
  object.cpp
  primitive.cpp
  screen.cpp
  shader.cpp
  texture.cpp
  window.cpp)

target_link_directories(${PROJECT_NAME} PUBLIC ../libs)
if(WIN32)
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)
  target_link_libraries(${PROJECT_NAME} PUBLIC freetyped)
elseif(UNIX)
  find_package(glfw3 REQUIRED)
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
  target_link_libraries(${PROJECT_NAME} PUBLIC freetype)
endif()

target_include_directories(${PROJECT_NAME} PUBLIC ../includes/headers)
target_include_directories(${PROJECT_NAME} PUBLIC ../includes)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.0)
