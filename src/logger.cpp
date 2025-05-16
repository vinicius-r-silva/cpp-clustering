#include "logger.hpp"

void logger::print_vector(const datapoint &vec) {
  for (const double &value : vec) {
    std::cout << value << " ";
  }
  std::cout << std::endl;
}

void logger::print_vector(const std::vector<datapoint> &vec) {
  for (const datapoint &inner_vec : vec) {
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

void logger::print_evaluation(const evaluation_result &result) {
  std::cout << "Dunn Index: " << result.dunn_index << std::endl;
  std::cout << "Silhouette Score: " << result.silhouette_score << std::endl;
  std::cout << "Davies-Bouldin Index: " << result.davies_bouldin_index << std::endl;
  std::cout << "Calinski-Harabasz Index: " << result.calinski_harabasz_index << std::endl;
  std::cout << "Within Cluster Sum of Squares (WCSS): " << result.within_cluster_sum_of_squares << std::endl;
}
