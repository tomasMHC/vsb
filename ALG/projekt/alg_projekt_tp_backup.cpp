#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
using namespace std;
/**
 * @file alg_projekt_tp.cpp
 * @brief Dokumentácia k projektu ALG – spracovanie grafu, DFS, komponenty, mosty.
 */

/**
 * @brief Načítanie hrán z textového súboru, kde každá řádka obsahuje dvě čísla reprezentující hranu mezi dvěma vrcholy.
 * @param filename 
 * @return std::vector<pair<int,int>> 
 */
std::vector<pair<int,int>> read_lines(const std::string& filename) {
    std::ifstream file(filename);
    vector<pair<int,int>> edges;
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
    for (int i = 0; i < adj.size(); i++) {
        if (visited[i] == false) {
            dfsRec(adj, visited, i, res);
        }
    }
    return res;
}

/**
 * @brief Rekurzívna funkcia pre hľadanie komponentov grafu metodou DFS (Depth-First Search). Táto funkcia navštívi všetky vrcholy, ktoré sú dosiahnuteľné z daného vrcholu `v`, a priradí im číslo komponentu `c` v zozname `comp`.
 * 
 * @param v 
 * @param c 
 * @param adj 
 * @param comp 
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
    for (int i = 0; i < adj.size(); i++) {
        if (!visited[i]) {
            components++;          // new component found
            dfsRec(adj, visited, i, res); // mark all vertices in this component as visited
        }
    }
    return components;
}

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

    for (int i = 0; i < edges.size(); i++) {     
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

bool isBridge(int edgeIndex,
              const vector<pair<int,int>> &edges,
              const vector<int> &removed)
{
    // 1. Zistíme najväčší vrchol
    int maxv = 0;
    for (auto &e : edges)
        maxv = max(maxv, max(e.first, e.second));

    // 2. Vytvoríme adjacency list BEZ edgeIndex a BEZ removed hrán
    vector<vector<int>> adj(maxv + 1);

    for (int i = 0; i < edges.size(); i++) {

        // preskočíme hranu, ktorú testujeme
        if (i == edgeIndex) continue;

        // preskočíme už odstránené hrany
        if (find(removed.begin(), removed.end(), i) != removed.end())
            continue;

        int u = edges[i].first;
        int v = edges[i].second;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // 3. Spočítame počet komponentov po odstránení hrany
    int after = components_count(adj);

    // 4. Spočítame pôvodný počet komponentov (bez removed hrán)
    vector<vector<int>> adj_full(maxv + 1);
    for (int i = 0; i < edges.size(); i++) {
        if (find(removed.begin(), removed.end(), i) != removed.end())
            continue;
        int u = edges[i].first;
        int v = edges[i].second;
        adj_full[u].push_back(v);
        adj_full[v].push_back(u);
    }
    int before = components_count(adj_full);

    // 5. Ak sa počet komponentov zvýšil → hrana je most
    return after > before;
}



/**
 * @brief Hlavná funkcia programu. Táto funkcia načíta hrany z textového súboru, vytvorí zoznam susedov, vypíše zoznam hrán a zoznam susedov, spočíta počet komponentov, nájde mosty, navrhne odstránenie niektorých hrán a pridanie nových hrán medzi komponentami, a nakoniec vypíše počet komponentov po navrhovanej oprave.
 */

int main() {
    std::vector<std::pair<int,int>> edges;
    int number_of_edges = 0;
    std::vector<std::vector<int>> adj;
    
    // načítanie hrán
    std::string filename = "RoadSystem1.txt";
    edges = read_lines(filename);
    cout << "Nazov suboru: " << filename << endl;
    adj = make_adj_list(edges);

    if (edges.empty()) {
        cout << "Graf nema zadne hrany.\n";
        return 0;
    }
    // Vypis edges listu
    cout<<"Edges list: \n";
    for (auto &e : edges) {
        number_of_edges++;
        cout << e.first << " " << e.second << "\n";
    }
    // Vypis adjacency listu
    cout << "Adjacency list:\n";
    for (int i = 0; i < adj.size(); i++) {
        cout << i << ": ";
        for (int to : adj[i]) {
            cout << to << " ";
        }
        cout << "\n";
    }

    // Počet komponent    
    int num_components = components_count(adj);
    cout << "Pocet komponent: " << num_components << endl;
    if (num_components == 1) {
        cout << "Graf je uz spojity, neni potreba zadne opravy.\n";
        return 0;
    }


    printf("DFS: \n");
    vector<int> comp(adj.size(), -1);
    vector<int> res = dfs(adj); 
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    
    cout << endl;



    // Hľadanie mostov
    vector<int> bridges = find_bridges(edges);
    cout << "-*-*- Mosty -*-*- " << endl;
    int i = 0;
    for (int bridge : bridges) {
        cout << "Je "<< edges[i].first << "-" << edges[i].second << " most?: " << bridge << " "  << "; " << endl;
        i++;
    }
    int non_bridges_count = std::count(bridges.begin(), bridges.end(), 0);

    if (non_bridges_count == 0) {
        cout << "Vsetky hrany su mostami, neni mozna oprava.\n";
        return 0;
    }
    else if (num_components > 1 && non_bridges_count >= (num_components - 1)) {
        cout << "Je mozna oprava\n";
    }

        // Priradenie cisla komponenty kazdemu vrcholu
    int c = 0;
    for (int i = 0; i < adj.size(); i++) {
        if (comp[i] == -1) {
            dfs_comp(i, c, adj, comp);
            c++;
        }
    }
    cout << "*-*-* Komponenty *-*-*\n";
    for (int i = 0; i < c; i++) {
        cout << "Komponenta " << i << ": ";
        for (int j = 0; j < comp.size(); j++) {
            if (comp[j] == i) {
                cout << j << " ";
            }
        }
        cout << "\n";
    }

    // // Zozbieranie hrán podľa komponentov
    // vector<vector<int>> edges_in_component(num_components);
    // for (int id = 0; id < edges.size(); id++) {
    //     int a = edges[id].first;
    //     int b = edges[id].second;
    //     if (comp[a] == comp[b]) { // hrana patri do komponenty
    //         int component_id = comp[a]; // alebo comp[b], su v tej istej komponente
    //         edges_in_component[component_id].push_back(id);
    //     }
    // }
    int removed_count = 0;
    vector<int> removed;
    for (int i = 0; i < edges.size() && removed_count < (num_components - 1); i++) {

        if (isBridge(i, edges, removed)) {
            cout << "Hrana " << edges[i].first << "-" << edges[i].second << " je mostom.\n";
        } 
        else {
            cout << "Hrana " << edges[i].first << "-" << edges[i].second << " neni mostom.\n";
            removed.push_back(i);
            removed_count++;
        }
    }

    cout << "Navrhovane odstranenie hrany: \n";
    for (int id : removed) {
        cout << edges[id].first << " " << edges[id].second << "\n";
    }

    std::vector<std::pair<int, int>> edges_new;
    for (int i = 0; i < num_components - 1; i++) {
        int rep1 = -1, rep2 = -1;
        for (int j = 0; j < comp.size(); j++) {
            if (comp[j] == i && rep1 == -1) {
                rep1 = j;
            }
            if (comp[j] == i + 1 && rep2 == -1) {
                rep2 = j;
            }
            if (rep1 != -1 && rep2 != -1) {
                break;
            }
        }
        edges_new.push_back({rep1, rep2});
    }

    cout << "Navrhovane pridanie hrany: \n";
    for (const auto &e : edges_new) {
        cout << e.first << " " << e.second << "\n";
    }

    std::vector<std::pair<int, int>> edges_final;
    for (int id = 0; id < edges.size(); ++id) {
        if (std::find(removed.begin(), removed.end(), id) == removed.end()) {
            edges_final.push_back(edges[id]); // ponechané hrany
        }
    }
    for (const auto &e : edges_new) {
        edges_final.push_back(e);
    }
    std::vector<std::vector<int>> adj_final = make_adj_list(edges_final);
    cout << "Pocet komponent po navrhovanej oprave: " << components_count(adj_final) << "\n";



    // // Odstranenie ciest ktore niesu mostami a zaroven v inych komponentoch aby nedoslo k rozbitiu komponentov
    // vector<int> removed;
    // int removed_count = 0;
    // std::vector<std::pair<int, int>> edges_final;
    // for (int c = 0; c < num_components; c++) {
    //     if (removed_count >= (num_components - 1)) {
    //         break;
    //     }
    //     for (int id : edges_in_component[c]) {
    //         if (bridges[id] == 0) {
    //             removed.push_back(id);
    //             removed_count++;
    //             break;
    //         }

    //     }
    // }
    // cout << "Navrhovane odstranenie hrany: \n";
    // for (int id : removed) {
    //     cout << edges[id].first << " " << edges[id].second << "\n";
    // }
    // for (int id = 0; id < edges.size(); ++id) {
    //     if (std::find(removed.begin(), removed.end(), id) == removed.end()) {
    //         edges_final.push_back(edges[id]); // ponechané hrany
    //     }
    // }

    // // Vytvorenie ciest medzi komponentami
    // std::vector<std::pair<int, int>> new_edges;
    // for (int i = 0; i < num_components-1; i++) {
    //     new_edges.push_back({-1, -1});
    //     for (int j = 0 ; j < comp.size(); j++) {
    //         if (comp[j] == i) {
    //             if (j==new_edges[i].second) { // ak je to ten isty vrchol ako predosly, tak ho preskocime aby nedoslo k vytvoreniu cyklu
    //                 continue;
    //             }
    //             int rep1 = j;
    //             new_edges[i].first = rep1;
    //             break;
    //         }
    //     }
    //     for (int j = 0; j < comp.size(); j++) {
    //         if (comp[j] == i + 1) {
                
    //             int rep2 = j;
    //             new_edges[i].second = rep2;
    //             break;
    //         }
    //     }
    // }
    // cout << "Navrhovane pridanie hrany: \n";
    // for (const auto &e : new_edges) {
    //     cout << e.first << " " << e.second << "\n";
    // }
    
    // for (const auto &e : new_edges) {
    //     edges_final.push_back(e);
    // }

    // std::vector<std::vector<int>> adj_final = make_adj_list(edges_final);
    // cout << "Pocet komponent po navrhovanej oprave: " << components_count(adj_final) << "\n";



    return 0;
}