#include "logger.hpp"

void logger::print_vector(const std::vector<double> &vec) {
  for (const double &value : vec) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

void logger::print_vector(const std::vector<std::vector<double>> &vec) {
  for (const std::vector<double> &inner_vec : vec) {
    print_vector(inner_vec);
  }
}

void logger::print_cluster(const std::vector<cluster> &clusters) {
  for (int i = 0; i < clusters.size(); ++i) {
    std::cout << "Cluster " << i + 1 << ":" << std::endl
              << "Centroid: ";
    print_vector(clusters[i].centroid);
    std::cout << "Data points: " << std::endl;
    print_vector(clusters[i].data);
    std::cout << std::endl;
  }
}