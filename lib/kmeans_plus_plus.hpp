#pragma once

#include "distance_calculator.hpp"
#include "evaluation.hpp"
#include "global.hpp"
#include "kmeans.hpp"

class kmeans_plus_plus {
private:
  const int MAX_ITERATIONS = 100;
  const int ATTEMPTS_PER_K_VALUE = 20;
  kmeans kmeans_calculator;
  datapoint get_initial_centroid(const std::vector<datapoint> &data);
  std::vector<datapoint> get_initial_centroids(const std::vector<datapoint> &data, int k, distance_metric distance_metric);
  std::vector<std::vector<datapoint>> get_multiple_initial_centroids(const std::vector<datapoint> &data, const int k, distance_metric distance_metric);

public:
  std::vector<cluster> calculate(const std::vector<datapoint> &data, const int k, evaluation_metric evaluation_metric, distance_metric distance_metric);
  clusterization_result calculate(const std::vector<datapoint> &data, distance_metric distance_metric = distance_metric::SQUARED_EUCLIDEAN);
};