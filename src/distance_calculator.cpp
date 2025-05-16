#include "distance_calculator.hpp"
#include <cmath>
#include <cstddef>

double distance_calculator::squared_euclidean(const datapoint &point1, const datapoint &point2) {
  double sum = 0.0;
  for (size_t i = 0; i < point1.size(); ++i) {
    double diff = point1[i] - point2[i];
    sum += diff * diff;
  }
  return sum;
}

double distance_calculator::euclidean(const datapoint &point1, const datapoint &point2) {
  return std::sqrt(squared_euclidean(point1, point2));
}

std::vector<double> distance_calculator::squared_euclidean(const datapoint &reference, const std::vector<datapoint> &points) {
  std::vector<double> distances(points.size());
  for (size_t i = 0; i < points.size(); ++i) {
    distances[i] = squared_euclidean(reference, points[i]);
  }
  return distances;
}

double distance_calculator::point_line_euclidean_distance(int x, double y, int x1, double y1, int x2, double y2) {
  double numerator = std::abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1);
  double denominator = std::sqrt(std::pow(y2 - y1, 2) + std::pow(x2 - x1, 2));
  return numerator / denominator;
}