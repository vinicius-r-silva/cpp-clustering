#pragma once

#include "cluster.hpp"
#include <vector>

enum evaluation_metric {
  SILHOUET_SCORE,
  WITHIN_CLUSTER_SUM_OF_SQUARES
};

enum evaluation_compare {
  WORSE = -1,
  EQUAL = 0,
  BETTER = 1
};

class evaluation_result {
public:
  double silhouette_score;
  double within_cluster_sum_of_squares;

  evaluation_result();
  evaluation_result(double silhouette_score, double within_cluster_sum_of_squares);
  evaluation_compare compare(const evaluation_result &other, evaluation_metric metric);
  double get_value(evaluation_metric metric) const;
};

class evaluation {
private:
public:
  static double calculate_silhouette_score(const std::vector<cluster> &clusters);
  static double calculate_within_cluster_sum_of_squares(const std::vector<cluster> &clusters);

  static evaluation_result evaluate(const std::vector<cluster> &clusters);
  static double evaluate(const std::vector<cluster> &clusters, evaluation_metric metric);
};