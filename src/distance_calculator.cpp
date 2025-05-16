#include "distance_calculator.hpp"
#include <cmath>
#include <cstddef>
#include <iostream>
#include <omp.h>

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

std::vector<std::vector<double>> distance_calculator::squared_euclidean(const std::vector<datapoint> &points1, const std::vector<datapoint> &points2) {
  bool is_symmetric = &points1 == &points2;
  std::vector<std::vector<double>> distances(points1.size(), std::vector<double>(points2.size()));

#pragma omp parallel for schedule(dynamic, 1)
  for (size_t i = 0; i < points1.size(); ++i) {
    if (is_symmetric) {
      for (size_t j = i + 1; j < points2.size(); ++j) {
        distances[i][j] = squared_euclidean(points1[i], points2[j]);
        distances[j][i] = distances[i][j];
      }
    } else {
      for (size_t j = 0; j < points2.size(); ++j) {
        distances[i][j] = squared_euclidean(points1[i], points2[j]);
      }
    }
  }
  return distances;
}

double distance_calculator::point_line_euclidean_distance(int x, double y, int x1, double y1, int x2, double y2) {
  double numerator = std::abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1);
  double denominator = std::sqrt(std::pow(y2 - y1, 2) + std::pow(x2 - x1, 2));
  return numerator / denominator;
}