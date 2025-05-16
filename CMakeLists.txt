cmake_minimum_required(VERSION 3.14)
project(ClusterGrouping)

set(CMAKE_CXX_STANDARD 17)

# Include directory for header files
include_directories(${CMAKE_SOURCE_DIR}/lib)

# Source files
set(SOURCES
  src/main.cpp
  src/distance_calculator.cpp
  src/input_generator.cpp
  src/logger.cpp
  src/cluster.cpp
  src/evaluation.cpp
  src/dbscan.cpp
  src/elbow_calculator.cpp
  src/kmeans/kmeans.cpp
  src/kmeans/naive_kmeans.cpp
  src/kmeans/kmeans_plus_plus.cpp
)

find_package(OpenMP REQUIRED)

# Create executable
add_executable(ClusterGrouping ${SOURCES})

if(OpenMP_CXX_FOUND)
  target_link_libraries(ClusterGrouping PUBLIC OpenMP::OpenMP_CXX)
endif()