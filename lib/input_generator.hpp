#pragma once

#include "global.hpp"
#include <vector>

class input_generator {
private:
public:
  static std::vector<datapoint> generate_random_data(int n, int d);
  // static std::vector<datapoint> generate_random_data_with_clusters(int n, int d, int k);
  // static std::vector<datapoint> generate_random_data_with_clusters_and_noise(int n, int d, int k, double noise_level);
  // static std::vector<datapoint> generate_random_data_with_clusters_and_noise_and_outliers(int n, int d, int k, double noise_level, int outliers);
};