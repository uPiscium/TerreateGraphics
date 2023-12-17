cmake_minimum_required(VERSION 3.20)
project(GeoFrameTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(../../GeoFrame GeoFrame)
add_executable(${PROJECT_NAME} main.cpp impls/drawingTest.cpp
                               impls/windowTest.cpp)
target_link_libraries(${PROJECT_NAME} GeoFrame)

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ../include)
target_include_directories(${PROJECT_NAME} PUBLIC ../GeoFrame)
