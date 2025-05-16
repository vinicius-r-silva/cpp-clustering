#pragma once

#include "cluster.hpp"
#include "evaluation.hpp"
#include <iostream>
#include <unordered_set>
#include <vector>

class logger {
public:
  static void print(const datapoint &vec);
  static void print(const std::vector<datapoint> &vec);
  static void print(const std::vector<int> &vec);
  static void print(const std::vector<std::vector<int>> &vec);
  static void print(const std::unordered_set<int> &set);
  static void print(const std::vector<cluster> &clusters);
  static void print(const evaluation_result &result);
  static void print(const clusterization_result &result);
};