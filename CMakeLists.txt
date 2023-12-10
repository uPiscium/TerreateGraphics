cmake_minimum_required(VERSION 3.20)
project(GeoFrame)
message(STATUS "Project name : " ${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
message(STATUS "C++ standard : " ${CMAKE_CXX_STANDARD})

add_library(${PROJECT_NAME} SHARED impls/buffer.cpp, impls/font.cpp)

target_include_directories(${PROJECT_NAME}
                           PUBLIC ${PROJECT_SOURCE_DIR}/includes)

if(WIN32)
  target_link_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/libs)
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw3)
  target_link_libraries(${PROJECT_NAME} PUBLIC freetyped)
elseif(UNIX)
    #target_link_directories(${PROJECT_NAME} PUBLIC /usr/local/lib) # path is not
                                                                 # correct
  target_link_libraries(${PROJECT_NAME} PUBLIC glfw)
endif()

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION 1.0.0)
