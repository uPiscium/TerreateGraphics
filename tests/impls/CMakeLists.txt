cmake_minimum_required(VERSION 3.20)
project(Tests)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(
  ${PROJECT_NAME}
  main.cpp drawingTest.cpp fontTest.cpp screenTest.cpp
  textureTest.cpp windowTest.cpp)

if (UNIX)
    message(STATUS "Environment is UNIX-like")
    target_link_libraries(${PROJECT_NAME} GeoFrame)
elseif (WIN32)
    message(STATUS "Environment is Windows")
    target_link_libraries(${PROJECT_NAME} GeoFrame)
endif ()

target_include_directories(${PROJECT_NAME} PUBLIC ../includes)
target_include_directories(${PROJECT_NAME} PUBLIC ../../includes)
target_include_directories(${PROJECT_NAME} PUBLIC ../../includes/headers)
