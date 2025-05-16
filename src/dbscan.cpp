#include "dbscan.hpp"
#include "distance_calculator.hpp"
#include "logger.hpp"

DatapointsCoreSplit split_core_points(const std::vector<datapoint> &data, const std::vector<std::vector<double>> &distance_matrix, const int min_points, const double min_distance) {
  std::vector<datapoint> core_points;
  std::vector<datapoint> non_core_points;

  const double min_distance_squared = min_distance * min_distance;
  std::vector<int> point_counts(data.size(), 0);
  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = 0; j < data.size(); ++j) {
      if (i != j && distance_matrix[i][j] <= min_distance_squared) {
        point_counts[i]++;
      }
    }

    if (point_counts[i] >= min_points) {
      core_points.push_back(data[i]);
    } else {
      non_core_points.push_back(data[i]);
    }
  }

  return {core_points, non_core_points};
}

std::vector<cluster> dbscan::calculate(const std::vector<datapoint> &data) {
  const int min_points = 5;
  const double min_distance = 0.1;

  std::vector<std::vector<double>> distance_matrix = distance_calculator::squared_euclidean(data, data);
  DatapointsCoreSplit points_split = split_core_points(data, distance_matrix, min_points, min_distance);

  std::cout << "core_points:" << std::endl;
  logger::print_vector(points_split.core_points);

  std::cout << std::endl
            << std::endl
            << "non_core_points:" << std::endl;
  logger::print_vector(points_split.non_core_points);

  // for (const auto &core_point : core_points) {
  //   cluster new_cluster;
  //   new_cluster.centroid = core_point;
  //   new_cluster.data.push_back(core_point);
  //   clusters.push_back(new_cluster);
  // }

  std::vector<cluster> clusters;
  return clusters;
}