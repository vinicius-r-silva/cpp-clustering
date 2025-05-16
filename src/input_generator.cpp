#include "input_generator.hpp"
#include <cmath>
#include <cstdlib>
#include <numeric>

std::vector<datapoint> input_generator::generate_pure_random_data(int n, int d) {
  std::vector<datapoint> data(n, datapoint(d));
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < d; ++j) {
      data[i][j] = double(rand()) / RAND_MAX;
    }
  }
  return data;
}

std::vector<datapoint> input_generator::generate_gaussian_clusters(int n, int d, int k, double spread) {
  std::vector<datapoint> data;

  if (k == 0) {
    k = rand() % ((int)std::sqrt(n));
  }

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

datapoint input_generator::random_unit_vector(int d) {
  datapoint vec(d);
  double norm = 0.0;
  for (int i = 0; i < d; ++i) {
    vec[i] = (double(rand()) / RAND_MAX) * 2.0 - 1.0;
    norm += vec[i] * vec[i];
  }
  norm = std::sqrt(norm);
  for (int i = 0; i < d; ++i)
    vec[i] /= norm;
  return vec;
}

void input_generator::normalize_vector(datapoint &vec) {
  double norm = std::sqrt(std::inner_product(vec.begin(), vec.end(), vec.begin(), 0.0));
  for (double &v : vec)
    v /= norm;
}

std::vector<datapoint> input_generator::generate_cosine_clusters(int n, int d, int k, double angle_noise) {
  std::vector<datapoint> data;
  std::vector<datapoint> directions;

  if (k == 0) {
    k = rand() % ((int)std::sqrt(n));
  }

  // Step 1: Generate k random directions (unit vectors)
  for (int i = 0; i < k; ++i)
    directions.push_back(random_unit_vector(d));

  // Step 2: Generate points around each direction
  for (int i = 0; i < n; ++i) {
    const datapoint &dir = directions[i % k];
    datapoint point(d);

    for (int j = 0; j < d; ++j) {
      // Small noise perpendicular to the direction vector
      point[j] = dir[j] + angle_noise * ((double(rand()) / RAND_MAX) - 0.5);
    }

    // Step 3: Normalize to unit vector
    normalize_vector(point);
    data.push_back(point);
  }

  return data;
}