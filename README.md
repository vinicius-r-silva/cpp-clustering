# ClusterGrouping

ClusterGrouping is a C++ project for clustering data using various algorithms. It provides tools for clustering, evaluation, and comparison of different clustering techniques.

## Features

- **Multiple Clustering Algorithms**: Currently includes naive k-means, with plans to add more algorithms like hierarchical clustering, DBSCAN, etc.
- **Evaluation Metrics**: Supports evaluation using metrics such as Dunn Index, Silhouette Score, Davies-Bouldin Index, Calinski-Harabasz Index, and Within-Cluster Sum of Squares (WCSS).
- **Distance Calculation**: Utilities for calculating distances between data points.
- **Input Generation**: Tools for generating synthetic input data for clustering.

## Requirements

- CMake 3.14 or higher
- C++17 compatible compiler

## Project Structure

- **`lib/`**: Contains header files for the project.
- **`src/`**: Contains implementation files for the project.

## Requirements

- CMake 3.14 or higher
- C++17 compatible compiler

## Build Instructions

1. Clone the repository:

   ```sh
   git clone <repository-url>
   cd cpp-clustering
   ```

2. Create a build directory and navigate to it:

   ```sh
   mkdir build
   cd build
   ```

3. Run CMake to configure the project:

   ```sh
   cmake ..
   ```

4. Build the project:

   ```sh
   make
   ```

5. Run the executable:
   ```sh
   ./ClusterGrouping
   ```

## Usage

The project is designed to be run as a standalone executable. Modify the `src/main.cpp` file to customize the input data, clustering parameters, and algorithms to compare.

## Planned Features

- **Additional Clustering Algorithms**: Implementation of algorithms like hierarchical clustering, DBSCAN, and others.
- **Algorithm Comparison**: Tools to compare the performance of different clustering algorithms using evaluation metrics.

```

```
