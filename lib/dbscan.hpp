#pragma once

#include "cluster.hpp"
#include "distance_calculator.hpp"
#include "global.hpp"
#include <vector>

// struct DatapointsCoreSplit {
//   std::vector<datapoint> core_points;
//   std::vector<datapoint> non_core_points;
// };

class dbscan {
private:
  const int MAX_ITERATIONS = 1000;
  std::vector<std::vector<int>> get_neighbors(const std::vector<datapoint> &data, const std::vector<std::vector<double>> &distance_matrix, const double min_distance);
  int get_random_core_point_index(const std::vector<std::vector<int>> &neighbors, int min_points);
  std::vector<int> label_core_points(const std::vector<datapoint> &data, std::vector<std::vector<int>> neighbors, const int min_points, const int initial_core_point_index);
  clusterization_result labels_to_clusters(const std::vector<datapoint> &data, const std::vector<int> &labels);
  std::vector<int> label_points(const std::vector<datapoint> &data, std::vector<std::vector<int>> neighbors, const int min_points, const int initial_core_point_index);
  std::vector<double> compute_k_distances(const std::vector<std::vector<double>> &distance_matrix, int k);

public:
  // std::vector<cluster> calculate(const std::vector<datapoint> &data);
  clusterization_result calculate(const std::vector<datapoint> &data, distance_metric metric = distance_metric::SQUARED_EUCLIDEAN);
};