#ifndef BRIDGES_H
#define BRIDGES_H

#include <vector>
#include <utility>

/**
 * @brief Skontroluje, ci je hrana mostom. Ak nie je - je možné ju odstrániť bez zvýšenia počtu komponent a tým pádom ju môžeme použiť na opravu grafu.
 * Funkcia vytvorí zoznam susedov bez testovanej hrany a bez už odstránených hrán, a potom spočíta počet komponentov. 
 * Porovnáva počet komponentov pred a po odstránení hrany, aby určila, či ide o most.
 * @param edgeIndex index hrany, ktorú testujeme
 * @param edges zoznam všetkých hrán
 * @param removed zoznam indexov odstráneneých hrán (kandidátov na opravu)
 * @return true ak je hrana mostom, false ak není mostom
 */
bool isBridge(size_t edgeIndex,
              std::vector<std::pair<int,int>> &edges,
              std::vector<int> &removed,
              int comp_count_original );

std::vector<int> find_bridges(std::vector<std::pair<int,int>> &edges);

#endif
