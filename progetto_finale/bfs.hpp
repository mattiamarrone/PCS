#pragma once
#include <iostream>
#include <vector>
#include <unordered_map>
#include "undirected_graph.hpp"
#include "fifo.hpp"

// Restituisce una mappa: per ogni nodo (chiave) indica chi è il suo padre (valore)
std::unordered_map<int, int> bfs(const undirected_graph<int>& G, int sorgente) {
    coda<int> c;
    
    std::unordered_map<int, bool> reached;
    std::unordered_map<int, int> padre;
    
    c.put(sorgente);
    reached[sorgente] = true;
    padre[sorgente] = -1; // Imposto la sentinella per la radice
    
    while (!c.empty()) {  // il ciclo funziona così: finchè la mia coda non si svuota: prendo l'elemento in fondo alla coda.
        int u = c.get();

        for (int node : G.neighbours(u)) {  // per ogni nodo vicino questo elemento controllo se lo ho già scoperto
            if (!reached[node]){  // se non lo ho scoperto, lo scopro e lo metto nella mia coda, so per certo che il padre di questo elemento è il mio u, perchè fin'ora non era stato scoeprto
                reached[node] = true;
                c.put(node);
                padre[node] = u;
            } // qui termina il for, ho la mia coda c completa con i nodi figli di u non soperti, prendo il primo e riparto. 
        }
    }
    return padre;
}

std::vector<int> bfs_shortest_path(const undirected_graph<int>& G, int inizio, int fine) {
    std::vector<int> path;
    
    // Eseguo la BFS partendo dal nodo di fine
    std::unordered_map<int, int> bfs_padre = bfs(G, fine);
    
    int nodo_attuale = inizio;
    
    while (nodo_attuale != -1) {
        path.push_back(nodo_attuale);
        
        // se il nodo attuale non ha un padre nella mappa,
        // e non è il nodo radice (-1), significa che i due nodi sono in componenti isolate.
        if (bfs_padre.find(nodo_attuale) == bfs_padre.end()) {
            std::cerr << "Errore: nessun percorso trovato tra i nodi." << std::endl;
            return {}; // Restituisco un vettore vuoto
        }
        
        nodo_attuale = bfs_padre[nodo_attuale];
    }
    
    return path;
}