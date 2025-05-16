#pragma once

#include "cluster.hpp"
#include "kmeans.hpp"
#include <unordered_set>
#include <vector>

class naive_kmeans {
private:
  kmeans kmeans_calculator;
  std::unordered_set<int> get_random_indices(int n, int k);
  std::vector<datapoint> get_random_centroids(const std::vector<datapoint> &data, int k);

public:
  std::vector<cluster> calculate(const std::vector<datapoint> &data);
};