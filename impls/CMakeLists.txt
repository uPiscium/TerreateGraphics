cmake_minimum_required(VERSION 3.20)
project(TerreateCore)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

include(FetchContent)

function(CloneGLFW)
  message(STATUS "Cloning GLFW...")
  set(GLFW_BUILD_EXAMPLES OFF)
  set(GLFW_BUILD_TESTS OFF)
  set(GLFW_BUILD_DOCS OFF)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.3.8)
  FetchContent_MakeAvailable(glfw)
  message(STATUS "GLFW cloned.")
endfunction()

function(CloneFreetype)
  message(STATUS "Cloning Freetype...")
  FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
    GIT_TAG VER-2-13-1)
  FetchContent_MakeAvailable(freetype)
  message(STATUS "Freetype cloned.")
endfunction()

function(SetIncludes)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes/deps)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes/math)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes/glsl)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes)
endfunction()

function(SetLibs)
  cloneglfw()
  clonefreetype()
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
  target_link_libraries(${PROJECT_NAME} PUBLIC freetype)
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
    text.cpp
    texture.cpp
    window.cpp)
  setincludes()
  setlibs()
endfunction()

build()
