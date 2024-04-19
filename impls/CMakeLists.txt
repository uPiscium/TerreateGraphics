cmake_minimum_required(VERSION 3.20)
project(TerreateCore)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

add_library(
  ${PROJECT_NAME} STATIC
  animation.cpp
  buffer.cpp
  core.cpp
  event.cpp
  font.cpp
  gl.cpp
  job.cpp
  model.cpp
  object.cpp
  scene.cpp
  screen.cpp
  shader.cpp
  skeleton.cpp
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

target_include_directories(${PROJECT_NAME} PUBLIC ../includes/deps)
target_include_directories(${PROJECT_NAME} PUBLIC ../includes/math)
target_include_directories(${PROJECT_NAME} PUBLIC ../includes)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.0)
