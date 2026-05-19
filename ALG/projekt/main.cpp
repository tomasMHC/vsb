#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

#include "graph.h"
#include "bridges.h"
#include "builder.h"

int main(int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Pouzitie: " << argv[0] << " <nazov_suboru>\n";
        return 1;
    }

    std::vector<std::pair<int,int>> edges;
    int number_of_edges = 0;
    std::vector<std::vector<int>> adj;
    
    // načítanie hrán
    std::string filename = argv[1];
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
    print_adj_list(adj);

    // Počet komponent    
    size_t num_components = components_count(adj);
    cout << "Pocet komponent: " << num_components << endl;
    if (num_components == 1) {
        cout << "Graf je uz spojity, neni potreba zadne opravy.\n";
        return 0;
    }

// // Hľadanie mostov 
//     std::vector<int> bridges = find_bridges(edges);
//     cout << "-*-*- Mosty -*-*- " << endl;
//     size_t i = 0;
//     // for (int bridge : bridges) {
//     //     cout << "Je "<< edges[i].first << "-" << edges[i].second << " most?: " << bridge << " "  << "; " << endl;
//     //     i++;
//     // }
//     int non_bridges_count = std::count(bridges.begin(), bridges.end(), 0);
//     if (non_bridges_count == 0) {
//         cout << "Vsetky hrany su mostami, neni mozna oprava.\n";
//         return 0;
//     }
//     else if (num_components > 1 && non_bridges_count >= (num_components - 1)) {
//         cout << "Je mozna oprava\n";
//     }
    // cout << "*-*-* Komponenty *-*-*\n";
    // for (int i = 0; i < c; i++) {
    //     cout << "Komponenta " << i << ": ";
    //     for (int j = 0; j < comp.size(); j++) {
    //         if (comp[j] == i) {
    //             cout << j << " ";
    //         }
    //     }
    //     cout << "\n";
    // }

    std::vector<int> to_remove = find_edges_to_remove(edges, num_components);
    if (to_remove.size() < (num_components - 1)) {
        cout << "Vsetky hrany su mostami alebo nie je možné odstrániť dostatok ciest --> neni mozna oprava !!\n";
        return 0;
    }
    else {
        cout << "Je mozna oprava...\n";
    }

    cout << "Navrhovane odstranenie hrany: \n";
    for (int id : to_remove) {
        cout << edges[id].first << " " << edges[id].second << "\n";
    }
    
    std::vector<std::pair<int, int>> edges_new;
    edges_new = edges_to_create(adj);
    cout << "Navrhovane pridanie hrany: \n";
    for (const auto &e : edges_new) {
        cout << e.first << " " << e.second << "\n";
    }

    // Vytvorenie finálneho zoznamu hrán po navrhovanej oprave
    std::vector<std::pair<int, int>> edges_final;
    for (size_t id = 0; id < edges.size(); ++id) {
        if (std::find(to_remove.begin(), to_remove.end(), id) == to_remove.end()) {
            edges_final.push_back(edges[id]); // ponechané hrany
        }
    }
    for (const auto &e : edges_new) {
        edges_final.push_back(e);
    }
    
    std::vector<std::vector<int>> adj_final = make_adj_list(edges_final);
    cout << "Pocet komponent po navrhovanej oprave: " << components_count(adj_final) << "\n";

    return 0;
}