#include <bits/stdc++.h>

#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

vector<vector<pair<int,int>>> adj;   // adj[v] = { (to, edge_id) }
vector<int> comp;                    // komponenta každého vrcholu
vector<int> tin, low;
vector<bool> visited;
vector<bool> is_bridge;

std::vector<pair<int,int>> read_lines(const std::string& filename) {
    std::ifstream file(filename);
    vector<pair<int,int>> edges;
    int a, b;
    while (file >> a >> b) {
        edges.push_back({a, b});
    }
    return edges;
}

int timer = 0;

// DFS na hľadanie komponent
void dfs_comp(int v, int c) {
    comp[v] = c;
    for (auto &p : adj[v]) {
        int to = p.first;
        if (comp[to] == -1) {
            dfs_comp(to, c);
        }
    }
}

// DFS na hľadanie mostov (Tarjan)
void dfs_bridge(int v, int parent_edge) {
    visited[v] = true;
    tin[v] = low[v] = timer++;

    for (auto &p : adj[v]) {
        int to = p.first;
        int id = p.second;

        if (id == parent_edge) continue; // nevracaj sa cez tú istú hranu

        if (visited[to]) {
            // spätná hrana
            low[v] = min(low[v], tin[to]);
        } else {
            // stromová hrana
            dfs_bridge(to, id);
            low[v] = min(low[v], low[to]);

            if (low[to] > tin[v]) {
                is_bridge[id] = true; // našli sme most
            }
        }
    }
}

void asciiDFS(int v, int parent, vector<vector<int>>& adj,
              vector<bool>& visited, string prefix, bool last) {
    cout << prefix;

    if (parent == -1)
        cout << v << "\n";  // koreň
    else
        cout << (last ? "└── " : "├── ") << v << "\n";

    visited[v] = true;

    // prefix pre deti
    string newPrefix = prefix + (last ? "    " : "│   ");

    // spočítaj počet nenavštívených susedov
    vector<int> children;
    for (int to : adj[v]) {
        if (!visited[to])
            children.push_back(to);
    }

    for (int i = 0; i < children.size(); i++) {
        asciiDFS(children[i], v, adj, visited, newPrefix, i == children.size() - 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<pair<int,int>> edges;
  
    // načítanie hrán
    edges = read_lines("RoadSystem2.txt");

    if (edges.empty()) {
        cout << "Graf nema zadne hrany.\n";
        return 0;
    }

    // zisti najväčší vrchol
    int maxv = 0;
    for (auto &e : edges) {
        maxv = max(maxv, max(e.first, e.second));
    }
    int n = maxv + 1;

    adj.assign(n, {});

    is_bridge.assign(edges.size(), false);

    // vytvor adjacency list
    for (int i = 0; i < (int)edges.size(); i++) {
        auto [a, b] = edges[i];
        adj[a].push_back({b, i});
        adj[b].push_back({a, i});
    }

    // 1. Najdi komponenty
    comp.assign(n, -1);
    int c = 0;
    vector<int> reps;

    for (int i = 0; i < n; i++) {
        if (comp[i] == -1) {
            dfs_comp(i, c);
            reps.push_back(i);
            c++;
        }
    }

    cout << "Pocet komponent: " << c << "\n";

    if (c == 1) {
        cout << "Oprava neni nutna, graf je jiz souvisly.\n";
        return 0;
    }

    // 2. Najdi mosty
    visited.assign(n, false);
    tin.assign(n, -1);
    low.assign(n, -1);
    timer = 0;

    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_bridge(i, -1);
        }
    }

    // 3. Zozbieraj nemostové hrany
    vector<int> non_bridges;
    for (int i = 0; i < (int)edges.size(); i++) {
        if (!is_bridge[i]) {
            non_bridges.push_back(i);
        }
    }

    if ((int)non_bridges.size() < c - 1) {
        cout << "Uloha neni resitelna - malo nemostovych hran.\n";
        return 0;
    }

    // 4. Vyber hrany na odstranenie
    vector<pair<int,int>> removed;
    for (int i = 0; i < c - 1; i++) {
        int id = non_bridges[i];
        removed.push_back(edges[id]);
    }

    // 5. Vytvor hrany na pridanie
    vector<pair<int,int>> added;
    for (int i = 0; i < c - 1; i++) {
        added.push_back({reps[i], reps[i+1]});
    }

    // 6. Výstup
    cout << "Odstranene hrany:\n";
    for (auto &e : removed) {
        cout << e.first << " " << e.second << "\n";
    }

    cout << "Vlozene hrany:\n";
    for (auto &e : added) {
        cout << e.first << " " << e.second << "\n";
    }

    cout << "Pocet komponent po oprave: 1\n";

    // ASCII vizualizácia grafu
    vector<vector<int>> adj_simple(n);
    for (auto &e : edges) {
        adj_simple[e.first].push_back(e.second);
        adj_simple[e.second].push_back(e.first);
    }

    vector<bool> visited_ascii(n, false);

    cout << "\nASCII mapa grafu:\n";
    for (int i = 0; i < n; i++) {
        if (!visited_ascii[i]) {
            cout << "Komponenta:\n";
            asciiDFS(i, -1, adj_simple, visited_ascii, "", true);
            cout << "\n";
        }
    }

    return 0;
}
