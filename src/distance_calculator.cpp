#include "distance_calculator.hpp"
#include <cmath>
#include <cstddef>

double distance_calculator::squared_euclidean(const std::vector<double> &point1, const std::vector<double> &point2) {
  double sum = 0.0;
  for (size_t i = 0; i < point1.size(); ++i) {
    double diff = point1[i] - point2[i];
    sum += diff * diff;
  }
  return sum;
}

double distance_calculator::euclidean(const std::vector<double> &point1, const std::vector<double> &point2) {
  return std::sqrt(squared_euclidean(point1, point2));
}