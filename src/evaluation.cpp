#include "evaluation.hpp"
#include "distance_calculator.hpp"
#include "logger.hpp"
#include <cmath>
#include <iostream>
#include <vector>

double evaluation::calculate_dunn_index(const std::vector<cluster> &clusters) {
  return 0;
}

double evaluation::calculate_silhouette_score(const std::vector<cluster> &clusters) {
  return 0;
}

double evaluation::calculate_davies_bouldin_index(const std::vector<cluster> &clusters) {
  return 0;
}

double evaluation::calculate_calinski_harabasz_index(const std::vector<cluster> &clusters) {
  return 0;
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
  double dunn_index = calculate_dunn_index(clusters);
  double silhouette_score = calculate_silhouette_score(clusters);
  double davies_bouldin_index = calculate_davies_bouldin_index(clusters);
  double calinski_harabasz_index = calculate_calinski_harabasz_index(clusters);
  double wcss = calculate_within_cluster_sum_of_squares(clusters);

  evaluation_result result = evaluation_result(dunn_index, silhouette_score, davies_bouldin_index, calinski_harabasz_index, wcss);
  // logger::print(result);
  return result;
}

double evaluation::evaluate(const std::vector<cluster> &clusters, evaluation_metric metric) {
  return evaluate(clusters).get_value(metric);
}

// TODO split this into multiple files
evaluation_result::evaluation_result()
    : dunn_index(std::numeric_limits<double>::min()), silhouette_score(std::numeric_limits<double>::min()), davies_bouldin_index(std::numeric_limits<double>::max()), calinski_harabasz_index(std::numeric_limits<double>::min()), within_cluster_sum_of_squares(std::numeric_limits<double>::max()) {}

evaluation_result::evaluation_result(double dunn_index, double silhouette_score, double davies_bouldin_index, double calinski_harabasz_index, double within_cluster_sum_of_squares)
    : dunn_index(dunn_index), silhouette_score(silhouette_score), davies_bouldin_index(davies_bouldin_index), calinski_harabasz_index(calinski_harabasz_index), within_cluster_sum_of_squares(within_cluster_sum_of_squares) {}

double evaluation_result::get_value(evaluation_metric metric) const {
  // change to strategy pattern
  switch (metric) {
  case DUMM_INDEX:
    return dunn_index;
  case SILHOUET_SCORE:
    return silhouette_score;
  case DAVIES_BOULDIN_INDEX:
    return davies_bouldin_index;
  case CALINSKI_HARABASZ_INDEX:
    return calinski_harabasz_index;
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
  case DUMM_INDEX:
  case SILHOUET_SCORE:
  case CALINSKI_HARABASZ_INDEX:
    return this_value > other_value ? BETTER : (this_value < other_value ? WORSE : EQUAL);

  case DAVIES_BOULDIN_INDEX:
  case WITHIN_CLUSTER_SUM_OF_SQUARES:
    return this_value < other_value ? BETTER : (this_value > other_value ? WORSE : EQUAL);

  default:
    return EQUAL;
  }
}