#include "logger.hpp"
#include <iomanip>
#include <ios>
#include <iostream>

void logger::print(const datapoint &vec) {
  for (const double &value : vec) {
    std::cout << std::fixed << std::setw(6) << std::setprecision(3) << value << " ";
  }
  std::cout << std::endl;
}

void logger::print(const std::vector<datapoint> &vec) {
  for (const datapoint &inner_vec : vec) {
    print(inner_vec);
  }
}

void logger::print(const std::vector<int> &vec) {
  for (const int &value : vec) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

void logger::print(const std::vector<std::vector<int>> &vec) {
  for (const std::vector<int> &inner_vec : vec) {
    print(inner_vec);
  }
}

void logger::print(const std::unordered_set<int> &set) {
  for (const int &value : set) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

void logger::print(const std::vector<cluster> &clusters) {
  for (int i = 0; i < clusters.size(); ++i) {
    std::cout << "Cluster " << i + 1 << ":" << std::endl
              << "Centroid: ";
    print(clusters[i].centroid);
    std::cout << "Data points: " << std::endl;
    print(clusters[i].data);
    std::cout << std::endl;
  }
}

void logger::print(const clusterization_result &result) {
  std::cout << "Number of clusters: " << result.clusters.size() << std::endl;
  std::cout << "Clusters:" << std::endl;
  print(result.clusters);
  std::cout << "Outliers:" << std::endl;
  print(result.outliers);
}

void logger::print(const evaluation_result &result) {
  std::cout << "Dunn Index: " << result.dunn_index << std::endl;
  std::cout << "Silhouette Score: " << result.silhouette_score << std::endl;
  std::cout << "Davies-Bouldin Index: " << result.davies_bouldin_index << std::endl;
  std::cout << "Calinski-Harabasz Index: " << result.calinski_harabasz_index << std::endl;
  std::cout << "Within Cluster Sum of Squares (WCSS): " << result.within_cluster_sum_of_squares << std::endl;
}
