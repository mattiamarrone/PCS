#pragma once

#include "unidirected_graph2.hpp"
#include <unordered_map>
#include <set>
#include <limits>

#pragma once

#include "unidirected_graph2.hpp"
#include <unordered_map>
#include <set>
#include <limits>

template<typename T>
unidirected_graph<T> dijkstra(const unidirected_graph<T>& G, const T& sorgente) {
    
    std::unordered_map<T, T> pred;   // ARRAY DEI PREDECESSORI
    std::unordered_map<T, int> dist; // ARRAY DELLE DISTANZE
    
    std::set<std::pair<int, T>> PQ; // ordina le pair partendo dal primo elemento: la distanza 

    const int INF = std::numeric_limits<int>::max();

    for (const auto& nodo : G.all_nodes()) {
        dist[nodo] = INF;
    }
    pred[sorgente] = sorgente;
    dist[sorgente] = 0;

    for (const auto& nodo : G.all_nodes()) {
        PQ.insert({dist[nodo], nodo});
    }

    while (!PQ.empty()) {
        
        auto it = PQ.begin();     // Prende l'elemento con distanza minima
        T u = it->second;         // Il nodo (u)
        PQ.erase(it);             // Lo rimuove dalla coda


        for (const auto& w : G.neighbours(u)) {
            

            int peso_arco = 1; 
            if (dist[w] > dist[u] + peso_arco) {
                PQ.erase({dist[w], w});
                dist[w] = dist[u] + peso_arco;
                pred[w] = u;
                PQ.insert({dist[w], w});
            }
        }
    }

    unidirected_graph<T> albero_risultante;
    for (const auto& [nodo, predecessore] : pred) {
        if (nodo != sorgente) {
            albero_risultante.add_edge(predecessore, nodo);
        }
    }

    return albero_risultante;
}