#pragma once

#include<list>
#include<vector>
#include<unordered_map>
#include<set>
#include "unidirected_graph2.hpp"
#include "lifo.hpp"
#include "fifo.hpp"


//la funzione graph_visit() :
// Prende in input due parametri, il grafo da visitare ed il nodo sorgente
// Prende un parametro template che specifica il tipo del contenitore da usare per effettuare la visita
// Restituisce un oggetto di tipo grafo contenente l’albero risultante dalla visita
template<typename T, typename Container>
unidirected_graph<T> graph_visit(const unidirected_graph<T>& grafo, const T& nodo_sorgente, Container& c){
	std::unordered_map<T, bool> reached;
	unidirected_graph<T> visited;
	for(const auto& nodo : grafo.all_nodes()){
		reached[nodo]=false;
	}
	c.put(nodo_sorgente);
	reached[nodo_sorgente]=true;
	while(!c.empty()){
		T u=c.get();
		for(const auto& w:grafo.neighbours(u)){
			if(!reached[w]){
				reached[w]=true;
				c.put(w);
				visited.add_edge(u,w);
			}
		}
	}
	return visited;
}