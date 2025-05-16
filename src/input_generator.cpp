#include "input_generator.hpp"
#include <cstdlib>

std::vector<datapoint> input_generator::generate_pure_random_data(int n, int d) {
  std::vector<datapoint> data(n, datapoint(d));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < d; ++j) {
      data[i][j] = double(rand()) / RAND_MAX;
    }
  }
  return data;
}

std::vector<datapoint> input_generator::generate_gaussian_clusters(int n, int d, int k, double spread = 0.1) {
  std::vector<datapoint> data;
  std::vector<datapoint> centers(k, datapoint(d));
  for (auto &center : centers) {
    for (int i = 0; i < d; ++i)
      center[i] = double(rand()) / RAND_MAX;
  }

  for (int i = 0; i < n; ++i) {
    const datapoint &center = centers[i % k];
    datapoint point(d);
    for (int j = 0; j < d; ++j) {
      point[j] = center[j] + spread * ((double(rand()) / RAND_MAX) - 0.5);
    }
    data.push_back(point);
  }

  return data;
}

std::vector<datapoint> input_generator::generate_linear_separable(int n, int d) {
  std::vector<datapoint> data;
  for (int i = 0; i < n; ++i) {
    datapoint point(d);
    double sum = 0;
    for (int j = 0; j < d; ++j) {
      point[j] = double(rand()) / RAND_MAX;
      sum += point[j];
    }
    if (sum > d / 2.0) {
      for (int j = 0; j < d; ++j)
        point[j] += 0.2;
    }
    data.push_back(point);
  }
  return data;
}