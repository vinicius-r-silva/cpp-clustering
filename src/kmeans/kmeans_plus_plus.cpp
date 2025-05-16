#include "kmeans_plus_plus.hpp"
#include "distance_calculator.hpp"
#include "logger.hpp"
#include <algorithm>
#include <cmath>
#include <omp.h>
#include <unordered_map>
#include <unordered_set>

datapoint kmeans_plus_plus::get_initial_centroid(const std::vector<datapoint> &data) {
  int n = data.size();
  int d = data[0].size();

  auto randval = rand();
  size_t random_index = randval % n;

  datapoint centroid(d);
  for (int j = 0; j < d; ++j) {
    centroid[j] = data[random_index][j];
  }

  return centroid;
}

std::vector<datapoint> kmeans_plus_plus::get_initial_centroids(const std::vector<datapoint> &data, const int k) {
  int n = data.size();
  int d = data[0].size();
  std::vector<datapoint> centroids;

  centroids.push_back(get_initial_centroid(data));

  for (int i = 1; i < k; ++i) {
    double total_distance = 0.0;
    std::vector<double> distances(n, 0.0);

    for (int j = 0; j < n; ++j) {
      std::vector<double> centroid_distances = distance_calculator::squared_euclidean(data[j], centroids);
      double min_distance = *std::min_element(centroid_distances.begin(), centroid_distances.end());
      distances[j] = min_distance;
      total_distance += min_distance;
    }

    double random_value = static_cast<double>(rand()) / RAND_MAX * total_distance;
    double cumulative_distance = 0.0;

    for (int j = 0; j < n; ++j) {
      cumulative_distance += distances[j];
      if (cumulative_distance >= random_value) {
        centroids.push_back(data[j]);
        break;
      }
    }
  }

  return centroids;
}

std::vector<std::vector<datapoint>> kmeans_plus_plus::get_multiple_initial_centroids(const std::vector<datapoint> &data, const int k) {
  std::vector<std::vector<datapoint>> initial_centroids;
  for (int i = 0; initial_centroids.size() < ATTEMPTS_PER_K_VALUE && i < MAX_ITERATIONS; ++i) {

    std::vector<datapoint> new_initial_centroids = kmeans_plus_plus::get_initial_centroids(data, k);
    if (std::find(initial_centroids.begin(), initial_centroids.end(), new_initial_centroids) != initial_centroids.end())
      continue;

    initial_centroids.push_back(new_initial_centroids);
  }

  return initial_centroids;
}

std::vector<cluster> kmeans_plus_plus::calculate(const std::vector<datapoint> &data, const int k, evaluation_metric metric) {
  evaluation_result best_score = evaluation_result();
  std::vector<cluster> best_clusters;

  std::vector<std::vector<datapoint>> initial_centroids = get_multiple_initial_centroids(data, k);

  int i = 0;
  for (const std::vector<datapoint> &initial_centroids : initial_centroids) {
    // std::cout << "attempt " << i++ << std::endl;
    std::vector<cluster> clusters = kmeans_calculator.calculate(data, initial_centroids);
    evaluation_result score = evaluation::evaluate(clusters);

    if (score.compare(best_score, metric) == evaluation_compare::BETTER) {
      best_score = score;
      best_clusters = clusters;
    }
  }

  return best_clusters;
}

clusterization_result kmeans_plus_plus::calculate(const std::vector<datapoint> &data) {
  evaluation_metric metric = evaluation_metric::WITHIN_CLUSTER_SUM_OF_SQUARES;
  std::unordered_map<int, double> k_to_score_map;
  std::unordered_map<int, std::vector<cluster>> k_to_cluster_map;

  const int initial_k = 1;
  const int max_k = std::sqrt(data.size() / 2);

  for (int k = initial_k; k <= max_k; ++k) {
    std::cout << "Calculating k = " << k << std::endl;
    std::vector<cluster> clusters = calculate(data, k, metric);
    evaluation_result score = evaluation::evaluate(clusters);

    k_to_score_map[k] = score.get_value(metric);
    k_to_cluster_map[k] = clusters;
  }

  int x1 = initial_k, x2 = max_k;
  double y1 = k_to_score_map[x1], y2 = k_to_score_map[x2];

  int best_k = initial_k;
  double max_distance = std::numeric_limits<double>::min();

  for (int k = initial_k; k <= max_k; ++k) {
    double y = k_to_score_map[k];
    double dist = distance_calculator::point_line_euclidean_distance(k, y, x1, y1, x2, y2);

    if (dist > max_distance) {
      max_distance = dist;
      best_k = k;
    }
  }

  return clusterization_result(k_to_cluster_map[best_k]);
}