#include "cluster.hpp"

cluster::cluster() : data(), centroid() {}

cluster::cluster(std::vector<std::vector<double>> data, std::vector<double> centroid) : data(data), centroid(centroid) {}