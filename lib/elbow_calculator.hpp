#pragma once

#include <vector>

class elbow_calculator {
public:
  static int find_elbow_index(const std::vector<double> &sorted_distances);
};