#ifndef REPAIR_H
#define REPAIR_H

#include <vector>
#include <utility>
#include "bridges.h"

std::vector<std::pair<int,int>> edges_to_create(std::vector<std::vector<int>> &adj);
std::vector<int> find_edges_to_remove(std::vector<std::pair<int,int>> &edges, size_t num_components_original);

#endif
