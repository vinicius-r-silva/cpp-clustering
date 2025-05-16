#include "naive_kmeans.hpp"
#include <cmath>

std::unordered_set<int> naive_kmeans::get_random_indices(int n, int k) {
  std::unordered_set<int> indices;
  while (indices.size() < k) {
    int index = rand() % n;
    indices.insert(index);
  }

  return indices;
}

std::vector<datapoint> naive_kmeans::get_random_centroids(const std::vector<datapoint> &data, int k) {
  int n = data.size();
  int d = data[0].size();
  std::unordered_set<int> random_indices = get_random_indices(n, k);
  std::vector<datapoint> centroids(k, datapoint(d));
  int i = 0;
  for (auto it = random_indices.begin(); it != random_indices.end(); it++, i++) {
    int index = *it;
    for (int j = 0; j < d; ++j) {
      centroids[i][j] = data[index][j];
    }
  }
  return centroids;
}

std::vector<cluster> naive_kmeans::calculate(const std::vector<datapoint> &data) {
  const int k = std::sqrt(data.size() / 2);
  std::vector<datapoint> centroids = get_random_centroids(data, k);
  return kmeans_calculator.calculate(data, centroids);
}