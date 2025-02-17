message(STATUS "Adding Terreate/core")

add_library(${PROJECT_NAME} STATIC executor.cpp uuid.cpp)
