#include "input_generator.hpp"
#include <cstdlib>

std::vector<std::vector<double>> input_generator::generate_random_data(int n, int d) {
  std::vector<std::vector<double>> data(n, std::vector<double>(d));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < d; ++j) {
      data[i][j] = static_cast<double>(rand()) / RAND_MAX;
    }
  }
  return data;
}