#pragma once

#include "global.hpp"
#include <vector>

enum distance_metric {
  SQUARED_EUCLIDEAN,
  EUCLIDEAN,
  COSINE
};

typedef double (*distance_function)(const datapoint &, const datapoint &);

class distance_calculator {
private:
  static distance_function get_distance_function(distance_metric metric);
  static double calculate(const datapoint &point1, const datapoint &point2, distance_function distance_func);
  static std::vector<double> calculate(const datapoint &reference, const std::vector<datapoint> &points, distance_function distance_func);
  static std::vector<std::vector<double>> calculate(const std::vector<datapoint> &points1, const std::vector<datapoint> &points2, distance_function distance_func);

public:
  static double squared_euclidean(const datapoint &point1, const datapoint &point2);
  static double euclidean(const datapoint &point1, const datapoint &point2);
  static double cosine(const datapoint &point1, const datapoint &point2);

  static double calculate(const datapoint &point1, const datapoint &point2, distance_metric metric);
  static std::vector<double> calculate(const datapoint &reference, const std::vector<datapoint> &points, distance_metric metric);
  static std::vector<std::vector<double>> calculate(const std::vector<datapoint> &points1, const std::vector<datapoint> &points2, distance_metric metric);

  static double point_line_euclidean_distance(int x, double y, int x1, double y1, int x2, double y2);
};