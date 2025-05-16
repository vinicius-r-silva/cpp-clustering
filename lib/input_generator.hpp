#pragma once

#include "global.hpp"
#include <vector>

class input_generator {
private:
  static datapoint random_unit_vector(int d);
  static void normalize_vector(datapoint &vec);

public:
  static std::vector<datapoint> generate_pure_random_data(int n, int d);
  static std::vector<datapoint> generate_gaussian_clusters(int n, int d, int k = 0, double spread = 0.1);
  static std::vector<datapoint> generate_linear_separable(int n, int d);
  static std::vector<datapoint> generate_cosine_clusters(int n, int d, int k = 0, double angle_noise = 0.05);
};