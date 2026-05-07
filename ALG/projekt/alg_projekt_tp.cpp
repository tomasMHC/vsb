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

std::vector<pair<int,int>> read_lines(const std::string& filename) {
    std::ifstream file(filename);
    vector<pair<int,int>> edges;
    int a, b;
    while (file >> a >> b) {
        edges.push_back({a, b});
    }
    return edges;
}

void dfsRec(vector<vector<int>> &adj, vector<bool> &visited, int s, vector<int> &res) {
    
    visited[s] = true;

    res.push_back(s);

    // Recursively visit all adjacent 
    // vertices that are not visited yet
    for (int i : adj[s])
        if (visited[i] == false)
            dfsRec(adj, visited, i, res);
}

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
void dfs_comp(int v, int c, vector<vector<int>> &adj, vector<int> &comp) {
    comp[v] = c;
    for (int to : adj[v]) {
        if (comp[to] == -1)
            dfs_comp(to, c, adj, comp);
    }
}

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




int main() {
    std::vector<std::pair<int,int>> edges;
    std::vector<std::vector<int>> adj;
    
    // načítanie hrán
    std::string filename = "RoadSystem5.txt";
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
    
    printf("DFS: \n");
    vector<int> comp(adj.size(), -1);
    vector<int> res = dfs(adj); 
    for (int i = 0; i < res.size(); i++)
        cout << res[i] << " ";
    
    cout << endl;

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

    // Hľadanie mostov
    vector<int> bridges = find_bridges(edges);
    cout << "-*-*- Mosty -*-*- " << endl;
    int i = 0;
    for (int bridge : bridges) {
        cout << "Je "<< edges[i].first << "-" << edges[i].second << " most?: " << bridge << " "  << "; " << endl;
        i++;
    }

    // Zozbieranie hrán podľa komponentov
    vector<vector<int>> edges_in_component(num_components);
    for (int id = 0; id < edges.size(); id++) {
        int a = edges[id].first;
        int b = edges[id].second;
        if (comp[a] == comp[b]) { // hrana patri do komponenty
            int component_id = comp[a]; // alebo comp[b], su v tej istej komponente
            edges_in_component[component_id].push_back(id);
        }
    }
    
    // Odstranenie ciest ktore niesu mostami a zaroven v inych komponentoch aby nedoslo k rozbitiu komponentov
    vector<int> removed;
    std::vector<std::pair<int, int>> edges_final;
    for (int c = 0; c < num_components-1; c++) {
        for (int id : edges_in_component[c]) {
            if (bridges[id] == 0) {
                removed.push_back(id);
                break;
            }
        }
    }
    cout << "Navrhovane odstranenie hrany: \n";
    for (int id : removed) {
        cout << edges[id].first << " " << edges[id].second << "\n";
    }
    for (int id = 0; id < edges.size(); ++id) {
        if (std::find(removed.begin(), removed.end(), id) == removed.end()) {
            edges_final.push_back(edges[id]); // ponechané hrany
        }
    }

    // Vytvorenie ciest medzi komponentami
    std::vector<std::pair<int, int>> new_edges;
    for (int i = 0; i < num_components-1; i++) {
        new_edges.push_back({-1, -1});
        for (int j = 0 ; j < comp.size(); j++) {
            if (comp[j] == i) {
                if (j==new_edges[i].second) { // ak je to ten isty vrchol ako predosly, tak ho preskocime aby nedoslo k vytvoreniu cyklu
                    continue;
                }
                int rep1 = j;
                new_edges[i].first = rep1;
                break;
            }
        }
        for (int j = 0; j < comp.size(); j++) {
            if (comp[j] == i + 1) {
                
                int rep2 = j;
                new_edges[i].second = rep2;
                break;
            }
        }
    }
    cout << "Navrhovane pridanie hrany: \n";
    for (const auto &e : new_edges) {
        cout << e.first << " " << e.second << "\n";
    }
    
    for (const auto &e : new_edges) {
        edges_final.push_back(e);
    }

    std::vector<std::vector<int>> adj_final = make_adj_list(edges_final);
    cout << "Pocet komponent po navrhovanej oprave: " << components_count(adj_final) << "\n";

    return 0;
}