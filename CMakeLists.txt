# Build options
option(BUILD_LARGE_MATRIX "Build Program on Eigen with Large Matrices" ON)

# Require at least C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Default to CMake 3.16
cmake_minimum_required(VERSION 3.16)

# Define the project
project(eigendemo LANGUAGES CXX)

# Eigen header file directory
set(EIGEN_HEADER_DIR ${PROJECT_SOURCE_DIR}/deps/eigen)

# Platform flags
if(MSVC)
    set(
      variables
        CMAKE_C_FLAGS_DEBUG
        CMAKE_C_FLAGS_MINSIZEREL
        CMAKE_C_FLAGS_RELEASE
        CMAKE_C_FLAGS_RELWITHDEBINFO
        CMAKE_CXX_FLAGS_DEBUG
        CMAKE_CXX_FLAGS_MINSIZEREL
        CMAKE_CXX_FLAGS_RELEASE
        CMAKE_CXX_FLAGS_RELWITHDEBINFO
    )
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /MP /utf-8 /O2 /Ob2 /Oi /Ot /Oy")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -funroll-loops -fPIC -pthread -w -O3 -Wno-unknown-pragmas -Wno-unused-private-field")
endif()

# Standalone C++ Program for Analyzing Eigen Performance with Large Matrices
if(BUILD_LARGE_MATRIX)
  add_executable(largematrix large_matrix.cpp)
  target_include_directories(largematrix PRIVATE ${EIGEN_HEADER_DIR})
endif()
