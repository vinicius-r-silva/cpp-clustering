#pragma once

#include "cluster.hpp"
#include <iostream>
#include <vector>

class logger {
public:
  static void print_vector(const std::vector<double> &vec);
  static void print_vector(const std::vector<std::vector<double>> &vec);
  static void print_cluster(const std::vector<cluster> &clusters);
};