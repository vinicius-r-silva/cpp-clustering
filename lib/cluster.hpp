#pragma once

#include <vector>

class cluster {
public:
  std::vector<std::vector<double>> data;
  std::vector<double> centroid;
  cluster();
  cluster(std::vector<std::vector<double>> data, std::vector<double> centroid);
};