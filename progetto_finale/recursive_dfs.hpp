#pragma once
#include <unordered_map>
#include <set>
#include "undirected_graph.hpp"

void visita(const undirected_graph<int>& G, int u, std::unordered_map<int, bool>& reached, undirected_graph<int>& dfsG)
{
    reached[u] = true; // imposta il nodo come raggiunto
    std::set<int> neigh = G.neighbours(u); // trova tutti i vicini di u

    for (auto it = neigh.rbegin(); it != neigh.rend(); ++it) { // rbegin e rend mi fanno iterare da destra a sinistra, ++it in automatico si muove di conseguenza
        int v = *it;
        if (!reached[v]) {
            
            std::pair<char, double> peso_reale = G.get_weight(u, v);
            dfsG.add_edge(u, v, peso_reale);
            
            visita(G, v, reached, dfsG);
        }
    }
}

undirected_graph<int> recursive_dfs(const undirected_graph<int>& G, int sorgente)
{
    undirected_graph<int> dfsG;
    
    // La mappa si inizializza vuota, i nodi non presenti risultano false di default
    std::unordered_map<int, bool> reached;

    visita(G, sorgente, reached, dfsG);

    return dfsG;
}