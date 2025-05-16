#pragma once

#include "cluster.hpp"
#include "global.hpp"
#include <vector>

struct DatapointsCoreSplit {
  std::vector<datapoint> core_points;
  std::vector<datapoint> non_core_points;
};

class dbscan {
private:
  /* data */
public:
  std::vector<cluster> calculate(const std::vector<datapoint> &data);
};