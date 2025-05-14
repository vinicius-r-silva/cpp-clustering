// Given a sequence of N-dimensional data, write a program to group these data into multiple clusters. Make reasonable choices to decide how to cluster as well as how many clusters. Discuss any trade-offs involved.

#include "cluster.hpp"
#include "evaluation.hpp"
#include "input_generator.hpp"
#include "logger.hpp"
#include "naive_kmeans.hpp"
#include <iostream>
#include <vector>

int main() {
  const int n = 2;
  const int d = 100;
  naive_kmeans naive_kmeans;
  std::vector<std::vector<double>> data = input_generator::generate_random_data(d, n);

  // std::cout << "Data points:" << std::endl;
  // logger::print_vector(data);
  // std::cout << std::endl;

  std::vector<cluster> naive_kmeans_clusters = naive_kmeans.calculate(data); // Fit the kmeans model to the data
  // std::cout << "Naive KMeans Clusters:" << std::endl;
  // logger::print_cluster(naive_kmeans_clusters);

  std::cout << std::endl;
  std::cout << "Naive Kmeans Evaluation:" << std::endl;
  evaluation::evaluate(naive_kmeans_clusters);

  return 0;
}