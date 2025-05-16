#include "cluster.hpp"

cluster::cluster() : data(), centroid() {}

cluster::cluster(std::vector<datapoint> data, datapoint centroid) : data(data), centroid(centroid) {}