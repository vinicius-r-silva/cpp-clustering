#pragma once

#include "global.hpp"
#include <vector>

class distance_calculator {
private:
public:
  static double squared_euclidean(const datapoint &point1, const datapoint &point2);
  static double euclidean(const datapoint &point1, const datapoint &point2);
  static std::vector<double> squared_euclidean(const datapoint &reference, const std::vector<datapoint> &points);
  static double point_line_euclidean_distance(int x, double y, int x1, double y1, int x2, double y2);
};