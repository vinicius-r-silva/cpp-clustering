// Given a sequence of N-dimensional data, write a program to group these data into multiple clusters. Make reasonable choices to decide how to cluster as well as how many clusters. Discuss any trade-offs involved.

#include "cluster.hpp"
#include "dbscan.hpp"
#include "evaluation.hpp"
#include "input_generator.hpp"
#include "kmeans_plus_plus.hpp"
#include "logger.hpp"
#include "naive_kmeans.hpp"
#include <iostream>
#include <vector>

int main() {
  const int n = 1000000;
  const int d = 2;
  naive_kmeans naive_kmeans;
  kmeans_plus_plus kmeans_plus_plus;
  dbscan dbscan;
  std::vector<datapoint> data = input_generator::generate_random_data(n, d);

  std::cout << "Data points:" << std::endl;
  // logger::print_vector(data);
  std::cout << std::endl;

  // std::vector<cluster> naive_kmeans_clusters = naive_kmeans.calculate(data); // Fit the kmeans model to the data
  // std::cout << "Naive KMeans Clusters:" << std::endl;
  // logger::print_cluster(naive_kmeans_clusters);

  std::vector<cluster> kmeans_plus_plus_clusters = kmeans_plus_plus.calculate(data); // Fit the kmeans model to the data
  std::cout << "Kmeans plus plus Clusters:" << std::endl;
  logger::print_cluster(kmeans_plus_plus_clusters);
  std::cout << std::endl;

  // std::vector<cluster> dbscan_clusters = dbscan.calculate(data); // Fit the kmeans model to the data
  // std::cout << "dbscan Clusters:" << std::endl;
  // logger::print_cluster(dbscan_clusters);
  // std::cout << std::endl;

  // std::cout << "Naive Kmeans Evaluation:" << std::endl;
  // evaluation_result naive_kmeans_eval = evaluation::evaluate(naive_kmeans_clusters);
  // logger::print_evaluation(naive_kmeans_eval);

  std::cout << "Kmeans plus plus Evaluation:" << std::endl;
  evaluation_result kmeans_plus_plus_eval = evaluation::evaluate(kmeans_plus_plus_clusters);
  logger::print_evaluation(kmeans_plus_plus_eval);

  return 0;
}