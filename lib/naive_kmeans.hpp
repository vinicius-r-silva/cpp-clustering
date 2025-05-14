#pragma once

#include "cluster.hpp"
#include <unordered_set>
#include <vector>

class naive_kmeans {
private:
  const int MAX_ITERATIONS = 100;
  std::unordered_set<int> get_random_indices(int n, int k);
  std::vector<std::vector<double>> get_random_centroids(const std::vector<std::vector<double>> &data, int k);
  std::vector<std::vector<double>> get_new_centroids(const std::vector<std::vector<double>> &data, const std::vector<int> &labels, int k);
  std::vector<int> get_labels(const std::vector<std::vector<double>> &data, const std::vector<std::vector<double>> &centroids);
  std::vector<cluster> get_clusters(const std::vector<std::vector<double>> &data, const std::vector<int> &labels, std::vector<std::vector<double>> centroids);

public:
  std::vector<cluster> calculate(const std::vector<std::vector<double>> &data);
  std::vector<cluster> calculate(const std::vector<std::vector<double>> &data, int k);
};