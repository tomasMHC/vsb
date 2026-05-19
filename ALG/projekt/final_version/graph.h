#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <string>

std::vector<std::pair<int,int>> read_lines(const std::string& filename);

std::vector<std::vector<int>> make_adj_list(std::vector<std::pair<int,int>> &edges);
void print_adj_list(std::vector<std::vector<int>> &adj);

void dfsRec(std::vector<std::vector<int>> &adj,
            std::vector<bool> &visited,
            int s,
            std::vector<int> &res);

std::vector<int> dfs(std::vector<std::vector<int>> &adj);

void dfs_comp(int v,
              int c,
              std::vector<std::vector<int>> &adj,
              std::vector<int> &comp);

int components_count(std::vector<std::vector<int>> &adj);

#endif
