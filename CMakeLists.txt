cmake_minimum_required(VERSION 3.20)
option(TERREATEGRAPHICS_BUILD_TESTS "Build tests" ON)

add_subdirectory(impls)

if(TERREATEGRAPHICS_BUILD_TESTS)
  add_subdirectory(tests)
endif()
