#pragma once

#include "cluster.hpp"
#include <vector>

class evaluation {
private:
public:
  static double calculate_dunn_index(const std::vector<cluster> &clusters);
  static double calculate_silhouette_score(const std::vector<cluster> &clusters);
  static double calculate_davies_bouldin_index(const std::vector<cluster> &clusters);
  static double calculate_calinski_harabasz_index(const std::vector<cluster> &clusters);
  static double calculate_within_cluster_sum_of_squares(const std::vector<cluster> &clusters);

  static void evaluate(const std::vector<cluster> &clusters);
};