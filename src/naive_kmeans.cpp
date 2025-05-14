#include "naive_kmeans.hpp"
#include "distance_calculator.hpp"
#include "logger.hpp"
#include <cmath>
#include <iostream>

std::unordered_set<int> naive_kmeans::get_random_indices(int n, int k) {
  std::unordered_set<int> indices;
  while (indices.size() < k) {
    int index = rand() % n;
    indices.insert(index);
  }

  return indices;
}

std::vector<std::vector<double>> naive_kmeans::get_random_centroids(const std::vector<std::vector<double>> &data, int k) {
  int n = data.size();
  int d = data[0].size();
  std::unordered_set<int> random_indices = get_random_indices(n, k);
  std::vector<std::vector<double>> centroids(k, std::vector<double>(d));
  int i = 0;
  for (auto it = random_indices.begin(); it != random_indices.end(); it++, i++) {
    int index = *it;
    for (int j = 0; j < d; ++j) {
      centroids[i][j] = data[index][j];
    }
  }
  return centroids;
}

std::vector<int> naive_kmeans::get_labels(const std::vector<std::vector<double>> &data, const std::vector<std::vector<double>> &centroids) {
  int n = data.size();
  int k = centroids.size();
  std::vector<int> labels(n);

  for (int i = 0; i < n; ++i) {
    double min_distance = std::numeric_limits<double>::max();
    for (int j = 0; j < k; ++j) {
      double distance = distance_calculator::squared_euclidean(data[i], centroids[j]);
      if (distance < min_distance) {
        min_distance = distance;
        labels[i] = j;
      }
    }
  }
  return labels;
}

std::vector<std::vector<double>> naive_kmeans::get_new_centroids(const std::vector<std::vector<double>> &data, const std::vector<int> &labels, int k) {
  int n = data.size();
  int d = data[0].size();
  std::vector<int> counts(k, 0);
  std::vector<std::vector<double>> new_centroids(k, std::vector<double>(d, 0.0));

  for (int i = 0; i < n; ++i) {
    int label = labels[i];
    counts[label]++;
    for (int j = 0; j < d; ++j) {
      new_centroids[label][j] += data[i][j];
    }
  }
  for (int j = 0; j < k; ++j) {
    if (counts[j] > 0) {
      for (int l = 0; l < d; ++l) {
        new_centroids[j][l] /= counts[j];
      }
    }
  }
  return new_centroids;
}

std::vector<cluster> naive_kmeans::get_clusters(const std::vector<std::vector<double>> &data, const std::vector<int> &labels, std::vector<std::vector<double>> centroids) {
  const int n = data.size();
  const int k = centroids.size();
  std::vector<cluster> clusters(k);

  for (int i = 0; i < k; ++i) {
    clusters[i] = cluster({}, centroids[i]);
  }

  for (int i = 0; i < n; ++i) {
    clusters[labels[i]].data.push_back(data[i]);
  }
  return clusters;
}

std::vector<cluster> naive_kmeans::calculate(const std::vector<std::vector<double>> &data, int k) {
  std::vector<int> labels;
  std::vector<std::vector<double>> centroids;
  std::vector<std::vector<double>> new_centroids = get_random_centroids(data, k);

  int iter = 0;
  while (new_centroids != centroids && iter < MAX_ITERATIONS) {
    centroids = new_centroids;
    labels = get_labels(data, centroids);
    new_centroids = get_new_centroids(data, labels, k);
    iter++;
  }

  return get_clusters(data, labels, centroids);
}

std::vector<cluster> naive_kmeans::calculate(const std::vector<std::vector<double>> &data) {
  const int k = std::sqrt(data.size());
  return calculate(data, k);
}