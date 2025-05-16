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
  const int n = 5000;
  const int d = 2;
  naive_kmeans naive_kmeans;
  kmeans_plus_plus kmeans_plus_plus;
  dbscan dbscan;
  std::vector<datapoint> data = input_generator::generate_pure_random_data(n, d);

  std::cout << "Data points:" << std::endl;
  logger::print(data);
  std::cout << std::endl;

  // clusterization_result naive_kmeans_result = naive_kmeans.calculate(data); // Fit the kmeans model to the data
  // std::cout << "Naive KMeans Clusters:" << std::endl;
  // logger::print(naive_kmeans_result);

  std::cout << "Kmeans plus plus Clusters:" << std::endl;
  clusterization_result kmeans_plus_plus_result = kmeans_plus_plus.calculate(data); // Fit the kmeans model to the data
  logger::print(kmeans_plus_plus_result);
  std::cout << std::endl;

  std::cout << "dbscan Clusters:" << std::endl;
  clusterization_result dbscan_result = dbscan.calculate(data); // Fit the kmeans model to the data
  logger::print(dbscan_result);
  std::cout << std::endl;

  // std::cout << "Naive Kmeans Evaluation:" << std::endl;
  // evaluation_result naive_kmeans_eval = evaluation::evaluate(naive_kmeans_result.clusters);
  // logger::print(naive_kmeans_eval);

  std::cout << "Kmeans plus plus Evaluation:" << std::endl;
  evaluation_result kmeans_plus_plus_eval = evaluation::evaluate(kmeans_plus_plus_result.clusters);
  logger::print(kmeans_plus_plus_eval);

  std::cout << "dbscan Evaluation:" << std::endl;
  evaluation_result dbscan_eval = evaluation::evaluate(dbscan_result.clusters);
  logger::print(dbscan_eval);

  return 0;
}