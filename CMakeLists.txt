cmake_minimum_required(VERSION 3.1.0)

project(vaslib)

set(VL_BIN_DIR "bin" CACHE STRING "Binaries directory")
set(VL_INCLUDE_DIR "include" CACHE STRING "Includes directory")
set(VL_LIB_DIR "lib" CACHE STRING "Libraries directory")
set(VL_CONFIG_DIR "share/cmake" CACHE STRING "CMake config directory")

set(OUTPUT_DIR "${CMAKE_BINARY_DIR}/${PROJECT_NAME}")

add_subdirectory(src)
