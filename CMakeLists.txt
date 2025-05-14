cmake_minimum_required(VERSION 3.14)
project(ClusterGrouping)

set(CMAKE_CXX_STANDARD 17)

# Include directory for header files
include_directories(${CMAKE_SOURCE_DIR}/lib)

# Source files
set(SOURCES
  src/main.cpp
  src/naive_kmeans.cpp
  src/distance_calculator.cpp
  src/input_generator.cpp
  src/logger.cpp
  src/cluster.cpp
  src/evaluation.cpp
)

# Create executable
add_executable(ClusterGrouping ${SOURCES})