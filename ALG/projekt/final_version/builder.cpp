using namespace std;
#include <iostream>
#include "graph.h"
#include "bridges.h"
#include "builder.h"
#include <cstdlib> 

/**
     * @brief Návrh hrán na pridanie medzi komponentami. 
     * Funkcia prejde všetky vrcholy a pre každý vrchol, ktorý patrí do komponenty `i`, nájde prvý vrchol, ktorý patrí do komponenty `i + 1`. 
     * Tieto dva vrcholy sa potom použijú na vytvorenie novej hrany, ktorá bude pridaná do zoznamu `edges_new`. 
     * Tento proces sa opakuje pre všetky komponenty od 0 do `num_components - 1`, čím sa zabezpečí, že každá komponenta bude spojená s ďalšou komponentou.
     * @param comp, num_components
     */
std::vector<std::pair<int, int>> edges_to_create(std::vector<std::vector<int>> &adj) {
    std::vector<std::pair<int, int>> edges_new;
    size_t num_components = components_count(adj);
    // Priradenie cisla komponenty kazdemu vrcholu
    std::vector<int> comp(adj.size(), -1);
    size_t c = 0;
    for (size_t i = 0; i < adj.size(); i++) {
        if (comp[i] == -1) {
            dfs_comp(i, c, adj, comp);
            c++;
        }
    }
    for (size_t i = 0; i < num_components - 1; i++) {
        int rep1 = -1, rep2 = -1;
        for (size_t j = 0; j < comp.size(); j++) {
            if ((size_t)comp[j] == i && rep1 == -1) {
                rep1 = j;
            }
            if ((size_t)comp[j] == i + 1 && rep2 == -1) {
                rep2 = j;
            }
            if (rep1 != -1 && rep2 != -1) {
                break;
            }
        }
        edges_new.push_back({rep1, rep2});
        
    }
    return edges_new;
}

/**
 * @brief Cyklus prechádza hrany a zisťuje, či je hranu možné odstrániť (použiť na postavenie novej cesty) bez toho, aby sa zvýšil počet komponentov. 
 * Ak hrana nie je mostom, pridá sa do zoznamu `removed`, ktorý obsahuje indexy hrán, ktoré budeme ostraňovať.
 */
    
    std::vector<int> find_edges_to_remove(std::vector<std::pair<int, int>> &edges, size_t num_components_original) {
        std::vector<int> removed;
        size_t removed_count = 0;
        for (size_t i = 0; i < edges.size() && removed_count < (num_components_original - 1); i++) {
            if (isBridge(i, edges, removed, num_components_original)==false) {
                // cout << "Hrana " << edges[i].first << "-" << edges[i].second << " neni mostom.\n";
                removed.push_back(i);
                removed_count++;
                if (removed_count >= (num_components_original - 1)) {
                    break;
                }
            }
        }
        return removed;
    }