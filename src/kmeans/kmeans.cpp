#include "kmeans.hpp"
#include "distance_calculator.hpp"
#include <cmath>

std::vector<int> kmeans::get_labels(const std::vector<datapoint> &data, const std::vector<datapoint> &centroids) {
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

std::vector<datapoint> kmeans::get_new_centroids(const std::vector<datapoint> &data, const std::vector<int> &labels, int k) {
  int n = data.size();
  int d = data[0].size();
  std::vector<int> counts(k, 0);
  std::vector<datapoint> new_centroids(k, datapoint(d, 0.0));

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

std::vector<cluster> kmeans::get_clusters(const std::vector<datapoint> &data, const std::vector<int> &labels, const std::vector<datapoint> &centroids) {
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

std::vector<cluster> kmeans::calculate(const std::vector<datapoint> &data, const std::vector<datapoint> &initial_centroids) {
  std::vector<int> labels;
  std::vector<datapoint> centroids;
  std::vector<datapoint> new_centroids = initial_centroids;

  int iter = 0;
  int k = initial_centroids.size();

  while (new_centroids != centroids && iter < MAX_ITERATIONS) {
    centroids = new_centroids;
    labels = get_labels(data, centroids);
    new_centroids = get_new_centroids(data, labels, k);
    iter++;
  }

  return get_clusters(data, labels, centroids);
}