#include "evaluation.hpp"
#include "distance_calculator.hpp"
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
    for (const std::vector<double> &point : cluster.data) {
      wcss += distance_calculator::euclidean(point, cluster.centroid);
    }
    total_wcss += wcss;
  }

  return total_wcss;
}

void evaluation::evaluate(const std::vector<cluster> &clusters) {
  double dunn_index = calculate_dunn_index(clusters);
  double silhouette_score = calculate_silhouette_score(clusters);
  double davies_bouldin_index = calculate_davies_bouldin_index(clusters);
  double calinski_harabasz_index = calculate_calinski_harabasz_index(clusters);
  double wcss = calculate_within_cluster_sum_of_squares(clusters);

  std::cout << "Dunn Index: " << dunn_index << std::endl;
  std::cout << "Silhouette Score: " << silhouette_score << std::endl;
  std::cout << "Davies-Bouldin Index: " << davies_bouldin_index << std::endl;
  std::cout << "Calinski-Harabasz Index: " << calinski_harabasz_index << std::endl;
  std::cout << "Within Cluster Sum of Squares (WCSS): " << wcss << std::endl;
}