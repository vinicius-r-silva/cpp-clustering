#include "elbow_calculator.hpp"
#include "distance_calculator.hpp"
#include <cmath>
#include <vector>

int elbow_calculator::find_elbow_index(const std::vector<double> &values) {
  int n = values.size();
  int elbow_index = 0;
  double max_dist = 0;

  int x1 = 0, x2 = n - 1;
  double y1 = values.front(), y2 = values.back();

  for (int i = 0; i < n; ++i) {
    double x0 = i;
    double y0 = values[i];

    double dist = distance_calculator::point_line_euclidean_distance(x0, y0, x1, y1, x2, y2);

    if (dist > max_dist) {
      max_dist = dist;
      elbow_index = i;
    }
  }

  return elbow_index;
}