cmake_minimum_required(VERSION 3.20)
project(GeoFrame)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(${PROJECT_NAME} SHARED impls/buffer.cpp, impls/font.cpp)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${PROJECT_SOURCE_DIR}/includes)

if(WIN32)
  target_link_libraries(${PROJECT_NAME} PUBLIC lib/glfw3)
elseif(UNIX)
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.0)
