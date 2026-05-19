#include "bridges.h"
#include <iostream>
#include "graph.h"
#include <algorithm>
using namespace std;

/**
 * @brief Hľadanie mostov v grafe. Táto funkcia prejde všetky hrany grafu a v prípade, že odstránením danej hrany sa zvýši počet komponentov, ide o most. Mosty sú uložené v zozname `bridges`, kde hodnota 1 znamená, že hrana je mostom, a hodnota 0 znamená, že hrana nie je mostom. Funkcia vytvorí kópiu zoznamu hrán, aby mohla testovať odstránenie každej hrany bez ovplyvnenia pôvodného zoznamu. Počet komponentov sa porovnáva pred a po odstránení hrany, aby sa určil, či ide o most.
 * 
 * @param edges 
 * @return std::vector<int> 
 */
std::vector<int> find_bridges(std::vector<std::pair<int,int>> &edges) {
    std::vector<int> bridges(edges.size(), 0);
    std::vector<std::pair<int,int>> edges_copy = edges;
    //dsf na hľadanie mostov
    int maxv = 0;               // najprv musime zistit kolko vrcholov mame
    int component_original = 0;
    for (auto &e : edges) {
        maxv = max(maxv, max(e.first, e.second));
    }
    std::vector<std::vector<int>> adj(maxv + 1);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }

    component_original = components_count(adj);

    for (size_t i = 0; i < edges.size(); i++) {     
        // delete element at index i
        edges_copy = edges; // reset edges_copy to original edges
        edges_copy.erase(edges_copy.begin() + i);
        std::vector<std::vector<int>> adj2(maxv + 1);
        for (auto &e : edges_copy) {
            adj2[e.first].push_back(e.second);
            adj2[e.second].push_back(e.first);
        }

        if (components_count(adj2) > component_original) {
            cout << "Bridge found: " << edges[i].first << " " << edges[i].second << "\n";
            bridges[i] = 1;
        }
    }
    return bridges;
}


bool isBridge(size_t edgeIndex,
              std::vector<std::pair<int,int>> &edges,
              std::vector<int> &removed,
              int comp_count_original)
{
    // 1. Vytvoríme zoznam susedov bez testovanej hrany a bez už odstraněných hrán
    int maxv = 0;
    for (auto &e : edges) {
        maxv = max(maxv, max(e.first, e.second));
    }
    std::vector<std::vector<int>> adj(maxv + 1);
    
    for (size_t i = 0; i < edges.size(); i++) {
        // preskočíme hranu, ktorú testujeme
        if (i == edgeIndex) continue;
        // preskočíme už odstránené hrany
        if (std::find(removed.begin(), removed.end(), i) != removed.end())
            continue;

        int u = edges[i].first;
        int v = edges[i].second;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Spočítame počet komponentov po odstránení hrany
    int after = components_count(adj);

    // 4. Ak sa počet komponentov zvýšil → hrana je most
    return after > comp_count_original;
}