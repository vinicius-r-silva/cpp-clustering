#include "cluster.hpp"

cluster::cluster() : data(), centroid() {}
cluster::cluster(std::vector<datapoint> data, datapoint centroid) : data(data), centroid(centroid) {}

clusterization_result::clusterization_result() : clusters(), outliers() {}
clusterization_result::clusterization_result(std::vector<cluster> clusters) : clusters(clusters), outliers() {}
clusterization_result::clusterization_result(std::vector<cluster> clusters, std::vector<datapoint> outliers) : clusters(clusters), outliers(outliers) {}