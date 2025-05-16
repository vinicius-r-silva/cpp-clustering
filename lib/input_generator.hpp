#pragma once

#include "global.hpp"
#include <vector>

class input_generator {
private:
public:
  static std::vector<datapoint> generate_pure_random_data(int n, int d);
  static std::vector<datapoint> generate_gaussian_clusters(int n, int d, int k = 0, double spread = 0.1);
  static std::vector<datapoint> generate_linear_separable(int n, int d);
};