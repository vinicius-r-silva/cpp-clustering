#include "evaluation.hpp"
#include "distance_calculator.hpp"
#include "logger.hpp"
#include <cmath>
#include <iostream>
#include <vector>

double evaluation::calculate_silhouette_score(const std::vector<cluster> &clusters) {
  std::vector<double> silhouette_scores;

  for (int i = 0; i < clusters.size(); ++i) {
    const cluster &current_cluster = clusters[i];

    for (const datapoint &point : current_cluster.data) {
      double a = 0.0;
      int same_cluster_count = 0;

      for (const datapoint &other : current_cluster.data) {
        if (&point != &other) {
          a += distance_calculator::euclidean(point, other);
          ++same_cluster_count;
        }
      }

      if (same_cluster_count > 0)
        a /= same_cluster_count;

      double b = std::numeric_limits<double>::max();

      for (int j = 0; j < clusters.size(); ++j) {
        if (j == i || clusters[j].data.empty())
          continue;

        double distance_sum = 0.0;
        for (const datapoint &other : clusters[j].data) {
          distance_sum += distance_calculator::euclidean(point, other);
        }

        double mean_distance = distance_sum / clusters[j].data.size();
        if (mean_distance < b)
          b = mean_distance;
      }

      double s = 0.0;
      if (std::max(a, b) > 0.0)
        s = (b - a) / std::max(a, b);

      silhouette_scores.push_back(s);
    }
  }

  if (silhouette_scores.empty())
    return 0.0;

  double total_score = std::accumulate(silhouette_scores.begin(), silhouette_scores.end(), 0.0);
  return total_score / silhouette_scores.size();
}

double evaluation::calculate_within_cluster_sum_of_squares(const std::vector<cluster> &clusters) {
  const int k = clusters.size();
  double total_wcss = 0.0;

  for (int i = 0; i < k; ++i) {
    const cluster &cluster = clusters[i];
    double wcss = 0.0;
    if (cluster.centroid.size() == 0)
      continue;

    for (const datapoint &point : cluster.data) {
      wcss += distance_calculator::euclidean(point, cluster.centroid);
    }
    total_wcss += wcss;
  }

  return total_wcss;
}

evaluation_result evaluation::evaluate(const std::vector<cluster> &clusters) {
  double silhouette_score = calculate_silhouette_score(clusters);
  double wcss = calculate_within_cluster_sum_of_squares(clusters);

  evaluation_result result = evaluation_result(dunn_index, silhouette_score, davies_bouldin_index, calinski_harabasz_index, wcss);
  return result;
}

double evaluation::evaluate(const std::vector<cluster> &clusters, evaluation_metric metric) {
  return evaluate(clusters).get_value(metric);
}

evaluation_result::evaluation_result()
    : dunn_index(std::numeric_limits<double>::min()), silhouette_score(std::numeric_limits<double>::min()), davies_bouldin_index(std::numeric_limits<double>::max()), calinski_harabasz_index(std::numeric_limits<double>::min()), within_cluster_sum_of_squares(std::numeric_limits<double>::max()) {}

evaluation_result::evaluation_result(double silhouette_score, double within_cluster_sum_of_squares)
    : silhouette_score(silhouette_score), within_cluster_sum_of_squares(within_cluster_sum_of_squares) {}

double evaluation_result::get_value(evaluation_metric metric) const {
  switch (metric) {
  case SILHOUET_SCORE:
    return silhouette_score;
  case WITHIN_CLUSTER_SUM_OF_SQUARES:
    return within_cluster_sum_of_squares;
  default:
    return 0.0;
  }
}

evaluation_compare evaluation_result::compare(const evaluation_result &other, evaluation_metric metric) {
  double this_value = get_value(metric);
  double other_value = other.get_value(metric);

  switch (metric) {
  case SILHOUET_SCORE:
    return this_value > other_value ? BETTER : (this_value < other_value ? WORSE : EQUAL);

  case WITHIN_CLUSTER_SUM_OF_SQUARES:
    return this_value < other_value ? BETTER : (this_value > other_value ? WORSE : EQUAL);

  default:
    return EQUAL;
  }
}