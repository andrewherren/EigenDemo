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

# Standalone C++ Program for Analyzing Eigen Performance with Large Matrices
if(BUILD_LARGE_MATRIX)
  add_executable(largematrix large_matrix.cpp)
  target_include_directories(largematrix PRIVATE ${EIGEN_HEADER_DIR})
endif()
