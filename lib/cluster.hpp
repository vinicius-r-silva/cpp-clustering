#pragma once

#include "global.hpp"
#include <vector>

class cluster {
public:
  std::vector<datapoint> data;
  datapoint centroid;

  cluster();
  cluster(std::vector<datapoint> data, datapoint centroid);
};