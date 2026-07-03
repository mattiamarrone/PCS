#pragma once
#include <fstream>
#include <iostream>
#include "undirected_graph.hpp" 
#include <utility>
#include <map>
#include <string>
#include "undirected_edge.hpp"

std::pair<undirected_graph<int>, std::map<undirected_edge<int>, int>> lettura_file(const std::string& file) {
    undirected_graph<int> grafo;  // inizializzo il grafo da restituire 
    std::map<undirected_edge<int>, int> mappa;  // inizializzo la mappa che mi dirà a ogni arco il numero della resistenza o -1 per le tensioni
    
    std::ifstream fs(file); // Apre direttamente il file 
    
    if (!fs.is_open()) { 
        std::cerr << "Impossibile aprire il file." << std::endl;
        return {grafo, mappa}; // Ritorno vuoto
    }
    
    char tipo; 
	int id;
    double valore; 
    int from; 
    int to; 
    
    while (fs >> tipo >> id >> valore >> from >> to) { 
        // Costruisco il peso dell'arco
        std::pair<char, double> peso_arco;// es. (R,20), (V,10)
        if(tipo == 'V' && to < from){ // se percorro arco al contrario devo invertire il segno del valore di V
			peso_arco = {tipo, -valore}; 
            grafo.add_edge(from, to, peso_arco); 
        } else {
            peso_arco = {tipo, valore};
            grafo.add_edge(from, to, peso_arco); 
        }

        // inizializzo l'oggetto arco per usarlo come chiave
        undirected_edge<int> arco_corrente(from, to, peso_arco);

        if(tipo == 'R'){
            // estrae l'intero saltando il primo carattere 'R'
            mappa[arco_corrente] = id;
        }
		else continue; 
    }
    
    // Lo stream viene chiuso automaticamente dal distruttore di ifstream, 
    // ma la chiamata esplicita non è un errore.
    fs.close(); 
    return {grafo, mappa}; 
}