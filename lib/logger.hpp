#pragma once

#include "cluster.hpp"
#include "evaluation.hpp"
#include <iostream>
#include <vector>

class logger {
public:
  static void print_vector(const datapoint &vec);
  static void print_vector(const std::vector<datapoint> &vec);
  static void print_cluster(const std::vector<cluster> &clusters);
  static void print_evaluation(const evaluation_result &result);
};