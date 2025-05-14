#pragma once

#include <vector>

class distance_calculator {
private:
public:
  static double squared_euclidean(const std::vector<double> &point1, const std::vector<double> &point2);
  static double euclidean(const std::vector<double> &point1, const std::vector<double> &point2);
};