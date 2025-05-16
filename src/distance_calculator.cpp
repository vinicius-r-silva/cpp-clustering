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

double distance_calculator::cosine(const datapoint &point1, const datapoint &point2) {
  double dot_product = 0.0;
  double norm1 = 0.0;
  double norm2 = 0.0;

  for (size_t i = 0; i < point1.size(); ++i) {
    dot_product += point1[i] * point2[i];
    norm1 += point1[i] * point1[i];
    norm2 += point2[i] * point2[i];
  }

  if (norm1 == 0.0 || norm2 == 0.0) {
    return 1.0;
  }

  return 1.0 - (dot_product / (std::sqrt(norm1) * std::sqrt(norm2)));
}

distance_function distance_calculator::get_distance_function(distance_metric metric) {
  switch (metric) {
  case SQUARED_EUCLIDEAN:
    return squared_euclidean;
  case EUCLIDEAN:
    return euclidean;
  case COSINE:
    return cosine;
  default:
    throw std::invalid_argument("Invalid distance metric");
  }
}

double distance_calculator::calculate(const datapoint &point1, const datapoint &point2, distance_function distance_function) {
  return distance_function(point1, point2);
}

std::vector<double> distance_calculator::calculate(const datapoint &reference, const std::vector<datapoint> &points, distance_function distance_function) {
  std::vector<double> distances(points.size());
  for (size_t i = 0; i < points.size(); ++i) {
    distances[i] = distance_function(reference, points[i]);
  }
  return distances;
}

std::vector<std::vector<double>> distance_calculator::calculate(const std::vector<datapoint> &points1, const std::vector<datapoint> &points2, distance_function distance_function) {
  bool is_symmetric = &points1 == &points2;
  std::vector<std::vector<double>> distances(points1.size(), std::vector<double>(points2.size()));

#pragma omp parallel for schedule(dynamic, 1)
  for (size_t i = 0; i < points1.size(); ++i) {
    if (is_symmetric) {
      for (size_t j = i + 1; j < points2.size(); ++j) {
        distances[i][j] = distance_function(points1[i], points2[j]);
        distances[j][i] = distances[i][j];
      }
    } else {
      for (size_t j = 0; j < points2.size(); ++j) {
        distances[i][j] = distance_function(points1[i], points2[j]);
      }
    }
  }
  return distances;
}

double distance_calculator::calculate(const datapoint &point1, const datapoint &point2, distance_metric metric) {
  distance_function distance_func = get_distance_function(metric);
  return calculate(point1, point2, distance_func);
}

std::vector<double> distance_calculator::calculate(const datapoint &reference, const std::vector<datapoint> &points, distance_metric metric) {
  distance_function distance_func = get_distance_function(metric);
  return calculate(reference, points, distance_func);
}

std::vector<std::vector<double>> distance_calculator::calculate(const std::vector<datapoint> &points1, const std::vector<datapoint> &points2, distance_metric metric) {
  distance_function distance_func = get_distance_function(metric);
  return calculate(points1, points2, distance_func);
}

double distance_calculator::point_line_euclidean_distance(int x, double y, int x1, double y1, int x2, double y2) {
  double numerator = std::abs((y2 - y1) * x - (x2 - x1) * y + x2 * y1 - y2 * x1);
  double denominator = std::sqrt(std::pow(y2 - y1, 2) + std::pow(x2 - x1, 2));
  return numerator / denominator;
}