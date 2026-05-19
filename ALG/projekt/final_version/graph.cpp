#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
using namespace std;

/**
 * @brief Načítanie hrán z textového súboru, kde každá řádka obsahuje dvě čísla reprezentující hranu mezi dvěma vrcholy.
 * @param filename 
 * @return std::vector<pair<int,int>> 
 */
std::vector<pair<int,int>> read_lines(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file '" << filename << "'." << std::endl;
        exit( EXIT_FAILURE );
    }

    std::vector<pair<int,int>> edges;
    int a, b;
    while (file >> a >> b) {
        edges.push_back({a, b});
    }
    return edges;
}

/**
 * @brief Rekurzívna funkcia pre prechod grafu metodou DFS (Depth-First Search). Táto funkcia navštívi všetky vrcholy, ktoré sú dosiahnuteľné z daného vrcholu `s`, a pridá ich do výsledného zoznamu `res`.
 * 
 * @param adj 
 * @param visited 
 * @param s 
 * @param res 
 */
void dfsRec(vector<vector<int>> &adj, vector<bool> &visited, int s, vector<int> &res) {
    visited[s] = true;
    res.push_back(s);

    // Recursively visit all adjacent vertices that are not visited yet
    for (int i : adj[s])
        if (visited[i] == false)
            dfsRec(adj, visited, i, res);
}

/**
 * @brief Prechod grafu metodou DFS (Depth-First Search). Táto funkcia prejde všetky vrcholy grafu a v prípade, že narazí na neobídaný vrchol, spustí rekurzívnu funkciu `dfsRec` na tento vrchol. Výsledkom je zoznam všetkých vrcholov v poradí, v akom boli navštívené.
 * 
 * @param adj 
 * @return vector<int> 
 */
vector<int> dfs(vector<vector<int>> &adj) {
    vector<bool> visited(adj.size(), false);
    vector<int> res;

    // Loop through all vertices 
    // to handle disconnected graph
    for (size_t i = 0; i < adj.size(); i++) {
        if (visited[i] == false) {
            dfsRec(adj, visited, i, res);
        }
    }
    return res;
}

/**
 * @brief DFS funkcia na priradenie čísla komponenty každému vrcholu.
 * 
 * @param v vrchol, ktorému priradíme číslo komponenty
 * @param c číslo komponenty
 * @param adj zoznam susedov
 * @param comp zoznam komponentov, kde index reprezentuje vrchol a hodnota reprezentuje číslo komponenty, do které vrchol patri
 */
void dfs_comp(int v, int c, vector<vector<int>> &adj, vector<int> &comp) {
    comp[v] = c;
    for (int to : adj[v]) {
        if (comp[to] == -1)
            dfs_comp(to, c, adj, comp);
    }
}

/**
 * @brief Vytvorenie zoznamu susedov zo zoznamu hrán. Táto funkcia najprv zistí maximálny vrchol v zozname hrán, aby vedela, koľko vrcholov má graf. Potom vytvorí prázdny zoznam susedov pre každý vrchol a naplní ho na základe hrán. Každá hrana pridá suseda do zoznamu susedov pre oba vrcholy, ktoré spája.
 * 
 * @param edges 
 * @return std::vector<std::vector<int>> 
 */
std::vector<std::vector<int>> make_adj_list(std::vector<std::pair<int,int>> &edges) {
    int maxv = 0;
    // najprv musime zistit kolko vrcholov mame
    for (auto &e : edges) {
        maxv = max(maxv, max(e.first, e.second));
    }
    std::vector<std::vector<int>> adj(maxv + 1);
    for (auto &e : edges) {
        adj[e.first].push_back(e.second);
        adj[e.second].push_back(e.first);
    }
    return adj;
}
void print_adj_list(std::vector<std::vector<int>> &adj) {
    for (size_t i = 0; i < adj.size(); i++) {
        cout << i << ": ";
        for (int to : adj[i]) {
            cout << to << " ";
        }
        cout << "\n";
    }
}

/**
 * @brief Spočítanie počtu komponentov grafu. Táto funkcia prejde všetky vrcholy grafu a v prípade, že narazí na neobídaný vrchol, spustí rekurzívnu funkciu `dfsRec` na tento vrchol, aby označila všetky vrcholy v tej istej komponente ako navštívené. Počet komponentov sa zvyšuje o 1 vždy, keď sa nájde nový nenavštívený vrchol.
 * 
 * @param adj 
 * @return int 
 */
int components_count(vector<vector<int>> &adj) {
    vector<bool> visited(adj.size(), false);
    int components = 0;
    std::vector<int> res;
    for (size_t i = 0; i < adj.size(); i++) {
        if (!visited[i]) {
            components++;          // new component found
            dfsRec(adj, visited, i, res); // mark all vertices in this component as visited
        }
    }
    return components;
}
