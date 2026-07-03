#pragma once
#include <iostream>
#include <vector>
#include <set>
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include "lifo.hpp"
#include "fifo.hpp"
#include "graph_visit.hpp"


// implemento l'algoritmo dfs per cicli che non sono necessariamente minimi in input diamo il grafo, il nodo di partenza e il nodo di arrivo in arrivo voglio il percorso tra i due nodi, salvato come un vettore 

// prendendo ispirazione dal codice di dfs ricorsivo, ho bisogno di una funzione ausiliaria che esplora un singolo nodo e ne salva il percorso, successivamente una funzione principale 

bool esplora_nodo_cammino(int nodo_corrente, int nodo_arrivo, const undirected_graph<int>& albero_T, std::set<int>& nodi_visitati, std::vector<int>& path) { 

    nodi_visitati.insert(nodo_corrente); // aggiungo il nodo corrente ai nodi visitati
    path.push_back(nodo_corrente);       // aggiungo il nodo corrente al percorso

    if (nodo_corrente==nodo_arrivo) {
        return true;                 // se il nodo corrente e quello di arrivo sono uguale allora vuol dire che il percorso è costituito da un solo nodo, quindi resituisco true
    }

    for (const int& vicino:albero_T.neighbours(nodo_corrente)) {                                           // itero su tutti i vicini del nodo corrente, grafo.neighbours() è un vettore 
        if (nodi_visitati.find(vicino)==nodi_visitati.end()) {                                          // se il vicino non è stato già esplorato allora lo esploro
            if (esplora_nodo_cammino(vicino, nodo_arrivo, albero_T, nodi_visitati, path)==true) {          // se la chiamata ricorsiva restituisce true allora è stato trovato un percorso
                return true;
            }
        }
    }

    path.pop_back();                                                                                    // se il nodo corrente non è quello di arrivo allora non è stato trovato un percorso tra i due 
                                                                                                        // quindi rimuovo il nodo corrente dal percorso e restituisco false
    return false;                                                        

};

std::vector<std::vector<int>> calcola_tutti_i_cicli_dfs(const undirected_graph<int>& grafo, const undirected_graph<int>& albero_T) {
    std::vector<std::vector<int>> tutti_i_cicli;     // questo vettore conterrà tutti i cicli trovati, ognuno è rappresentato come un vettore di interi

    // calcoliamo il coalbero 
    undirected_graph<int> coalbero_C=grafo-albero_T;

    // iteriamo ora su ogni arco del coalbero
    for (const auto& arco:coalbero_C.all_edges()) {
        int u=arco.from();
        int v=arco.to();

        std::vector<int> path;
        std::set<int> nodi_visitati;

        if (esplora_nodo_cammino(u, v, albero_T, nodi_visitati, path) == true) {
            path.push_back(u);
            tutti_i_cicli.push_back(path);
        }
    }

    return tutti_i_cicli;
}




