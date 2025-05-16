#pragma once

#include "cluster.hpp"
#include "global.hpp"

class kmeans {
private:
  const int MAX_ITERATIONS = 100;
  std::vector<datapoint> get_new_centroids(const std::vector<datapoint> &data, const std::vector<int> &labels, int k);
  std::vector<int> get_labels(const std::vector<datapoint> &data, const std::vector<datapoint> &centroids);
  std::vector<cluster> get_clusters(const std::vector<datapoint> &data, const std::vector<int> &labels, const std::vector<datapoint> &centroids);

public:
  std::vector<cluster> calculate(const std::vector<datapoint> &data, const std::vector<datapoint> &initial_centroids);
};