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

class clusterization_result {
public:
  std::vector<cluster> clusters;
  std::vector<datapoint> outliers;

  clusterization_result();
  clusterization_result(std::vector<cluster> clusters);
  clusterization_result(std::vector<cluster> clusters, std::vector<datapoint> outliers);
};