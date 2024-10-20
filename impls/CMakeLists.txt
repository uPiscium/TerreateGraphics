cmake_minimum_required(VERSION 3.20)
project(TerreateGraphics)
message(STATUS "Project name : " ${PROJECT_NAME})

include(FetchContent)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

function(CloneTerreateCore)
  message(STATUS "Cloning TerreateCore...")
  set(TERREATECORE_BUILD_TESTS OFF)
  FetchContent_Declare(
    terreate_core
    GIT_REPOSITORY https://github.com/uPiscium/TerreateCore.git
    GIT_TAG main)
  FetchContent_MakeAvailable(terreate_core)
  message(STATUS "TerreateCore cloned.")
endfunction()

function(CloneGLFW)
  message(STATUS "Cloning GLFW...")
  set(GLFW_BUILD_EXAMPLES OFF)
  set(GLFW_BUILD_TESTS OFF)
  set(GLFW_BUILD_DOCS OFF)
  FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4)
  FetchContent_MakeAvailable(glfw)
  message(STATUS "GLFW cloned.")
endfunction()

function(CloneFreetype)
  message(STATUS "Cloning Freetype...")
  message(STATUS "This may take a while.")
  FetchContent_Declare(
    freetype
    GIT_REPOSITORY https://gitlab.freedesktop.org/freetype/freetype.git
    GIT_TAG VER-2-13-1)
  FetchContent_MakeAvailable(freetype)
  message(STATUS "Freetype cloned.")
endfunction()

function(SetIncludes)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes/deps)
  target_include_directories(${PROJECT_NAME} PUBLIC ../includes)
endfunction()

function(SetLibs)
  cloneterreatecore()
  cloneglfw()
  clonefreetype()
  target_link_libraries(${PROJECT_NAME} PUBLIC TerreateCore)
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
  target_link_libraries(${PROJECT_NAME} PUBLIC freetype)
endfunction()

function(Build)
  add_library(
    ${PROJECT_NAME} STATIC
    TerreateGraphics.cpp
    buffer.cpp
    compute.cpp
    converter.cpp
    event.cpp
    font.cpp
    gl.cpp
    globj.cpp
    joystick.cpp
    screen.cpp
    shader.cpp
    text.cpp
    texture.cpp
    window.cpp)
  set_target_properties(
    ${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
                               LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
  setincludes()
  setlibs()
endfunction()

build()
