#include "dbscan.hpp"
#include "distance_calculator.hpp"
#include "elbow_calculator.hpp"
#include "logger.hpp"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

std::vector<std::vector<int>> dbscan::get_neighbors(const std::vector<datapoint> &data, const std::vector<std::vector<double>> &distance_matrix, const double min_distance) {
  std::vector<std::vector<int>> neighbors(data.size(), std::vector<int>());

  for (size_t i = 0; i < data.size(); ++i) {
    for (size_t j = i + 1; j < data.size(); ++j) {
      if (i != j && distance_matrix[i][j] <= min_distance) {
        neighbors[i].push_back(j);
        neighbors[j].push_back(i);
      }
    }
  }

  return neighbors;
}

int dbscan::get_random_core_point_index(const std::vector<std::vector<int>> &neighbors, int min_points) {
  for (size_t i = 0; i < neighbors.size(); ++i) {
    int random_index = rand() % neighbors.size();
    if (neighbors[random_index].size() >= min_points) {
      return random_index;
    }
  }

  for (size_t i = 0; i < neighbors.size(); ++i) {
    if (neighbors[i].size() >= min_points) {
      return i;
    }
  }

  return -1;
}

std::vector<int> dbscan::label_core_points(const std::vector<datapoint> &data, std::vector<std::vector<int>> neighbors, const int min_points, const int initial_core_point_index) {
  std::vector<int> labels(data.size(), -1);
  labels[initial_core_point_index] = 0;

  std::unordered_set<int> consolidated_points;
  std::unordered_set<int> to_consolidate_points;
  std::unordered_set<int> missing_points;

  for (int i = 0; i < data.size(); ++i) {
    if (neighbors[i].size() >= min_points && i != initial_core_point_index) {
      missing_points.insert(i);
    }
  }

  int next_label = 1;
  to_consolidate_points.insert(initial_core_point_index);
  while (missing_points.size() > 0) {
    if (to_consolidate_points.empty()) {
      int first_index = *missing_points.begin();
      labels[first_index] = next_label;

      to_consolidate_points.insert(first_index);
      missing_points.erase(first_index);
      next_label++;
    }

    for (int points_index : std::unordered_set<int>(to_consolidate_points)) {
      int label_value = labels[points_index];
      for (int neighbor_index : neighbors[points_index]) {
        if (labels[neighbor_index] == -1 && neighbors[neighbor_index].size() >= min_points) {
          labels[neighbor_index] = label_value;
          to_consolidate_points.insert(neighbor_index);
          missing_points.erase(neighbor_index);
        }
      }

      to_consolidate_points.erase(points_index);
      consolidated_points.insert(points_index);
    }
  }

  return labels;
}

clusterization_result dbscan::labels_to_clusters(const std::vector<datapoint> &data, const std::vector<int> &labels) {
  int biggest_label = 0;
  std::vector<datapoint> outliers;
  std::unordered_map<int, cluster> clusters_map;
  for (size_t i = 0; i < data.size(); ++i) {
    int label = labels[i];
    biggest_label = std::max(biggest_label, label);

    if (label != -1) {
      if (clusters_map.find(label) == clusters_map.end()) {
        clusters_map[label] = cluster();
      }
      clusters_map[label].data.push_back(data[i]);
    } else {
      outliers.push_back(data[i]);
    }
  }

  std::vector<cluster> clusters(biggest_label + 1);
  for (int i = 0; i <= biggest_label; ++i) {
    clusters[i] = clusters_map[i];
  }

  clusterization_result result(clusters, outliers);
  return result;
}

std::vector<int> dbscan::label_points(const std::vector<datapoint> &data, std::vector<std::vector<int>> neighbors, const int min_points, const int initial_core_point_index) {
  std::vector<int> labels = label_core_points(data, neighbors, min_points, initial_core_point_index);

  for (int i = 0; i < data.size(); ++i) {
    for (int neighbor_index : neighbors[i]) {
      if (labels[neighbor_index] != -1) {
        labels[i] = labels[neighbor_index];
        break;
      }
    }
  }

  return labels;
}

std::vector<double> dbscan::compute_k_distances(const std::vector<std::vector<double>> &distance_matrix, int k) {
  int n = distance_matrix.size();
  std::vector<double> k_distances(n);

#pragma omp parallel for schedule(dynamic, 1)
  for (int i = 0; i < n; ++i) {
    std::vector<double> sorted = distance_matrix[i];
    std::sort(sorted.begin(), sorted.end());
    k_distances[i] = sorted[k];
  }

  std::sort(k_distances.begin(), k_distances.end());
  return k_distances;
}

clusterization_result dbscan::calculate(const std::vector<datapoint> &data, distance_metric metric) {
  const int min_points = data[0].size() + 1;
  std::vector<std::vector<double>> distance_matrix = distance_calculator::calculate(data, data, metric);

  std::vector<double> k_distances = compute_k_distances(distance_matrix, min_points - 1);
  int elbow_idx = elbow_calculator::find_elbow_index(k_distances);
  double min_distance = k_distances[elbow_idx] + 0.001;
  // double min_distance = k_distances[elbow_idx] + 0.0001;

  std::vector<std::vector<int>> neighbors = get_neighbors(data, distance_matrix, min_distance);
  int random_core_point_index = get_random_core_point_index(neighbors, min_points);
  if (random_core_point_index == -1) {
    return clusterization_result({}, data);
  }

  std::vector<int> labels = label_points(data, neighbors, min_points, random_core_point_index);
  std::vector<datapoint> clusters(labels.size());
  clusterization_result result = labels_to_clusters(data, labels);

  return result;
}