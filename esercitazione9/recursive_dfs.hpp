#pragma once

#include "unidirected_graph2.hpp"
#include<map>
template<typename T>

void esplora_nodo(const unidirected_graph<T>& G, const T& nodo, std::map<T, bool>& visitati, unidirected_graph<T>& grafo_risultante){
	visitati[nodo]=true;
	for(const auto& u : G.neighbours(nodo)){
		if(visitati[u]==false){
			grafo_risultante.add_edge(nodo, u);
			esplora_nodo(G, u, visitati, grafo_risultante);
		}
	}
}


template<typename T>
unidirected_graph<T> recursive_dfs(const unidirected_graph<T>& G, const T& nodo_sorgente){
	std::map<T, bool> visitati;
	for(const auto& nodo : G.all_nodes()){
		visitati[nodo]=false;
	}
	unidirected_graph<T> grafo_risultante;
	esplora_nodo(G,nodo_sorgente,visitati,grafo_risultante);
	return grafo_risultante;
}
		
