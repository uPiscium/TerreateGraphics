cmake_minimum_required(VERSION 3.20)
project(TerreateCore)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

function(SetIncludes)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes/deps)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes/math)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes/glsl)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes)
endfunction()

function(SetLibs)
  target_link_directories(${PROJECT_NAME} PUBLIC ../libs)
  if(WIN32)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)
    target_link_libraries(${PROJECT_NAME} PUBLIC freetyped)
  elseif(UNIX)
    find_package(glfw3 REQUIRED)
    target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
    target_link_libraries(${PROJECT_NAME} PUBLIC freetype)
  endif()
endfunction()

function(Build)
  add_library(
    ${PROJECT_NAME} STATIC
    TerreateCore.cpp
    animation.cpp
    buffer.cpp
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
  setincludes()
  setlibs()
endfunction()

build()
