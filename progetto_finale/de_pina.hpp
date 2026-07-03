#pragma once
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include "bfs.hpp"
#include <vector>
#include <iostream>

std::vector<bool> lifting(const undirected_graph<int>& G, const std::vector<bool>& S) {
	//parte 1 e 2
	int N = G.all_nodes().size(); //numero di nodi di G
	int E = G.all_edges().size(); //numero di archi di G
	
	undirected_graph<int> G_new;
	/*
	G_new avrà il doppio dei nodi di G.
	Siano n_i i={0,...,N} i nodi di G, i nodi di G_new sono m_j j={0,...,2N}.
	n_i+ = 2*n_i (m_j pari)
	n_i- = 2*n_i + 1 (m_j dispari)
	*/
	for (const auto& edge : G.all_edges()) {
		int e = G.edge_number(edge);
		if (S[e]) {
			G_new.add_edge(2*edge.from(),2*edge.to()+1);
			G_new.add_edge(2*edge.from()+1,2*edge.to());
		}
		else {
			G_new.add_edge(2*edge.from(),2*edge.to());
			G_new.add_edge(2*edge.from()+1,2*edge.to()+1);
		}
	}
	
	//parte 3 e 4
	std::vector<std::vector<bool>> C_vector; //vettore dei vettori di incidenza
	C_vector.resize(N);
	int c = 0; //contatore di C_vector
	for (const auto& node : G.all_nodes()) {
		
		auto path = bfs_shortest_path(G_new, 2*node, 2*node+1);
		std::vector<bool> C(E, false); //vettore d'incidenza
		for (size_t i=1; i<path.size(); i++) {
			undirected_edge edge(path[i-1]/2, path[i]/2); //dividendo per 2, ottengo il nodo n_i di G
			int index = G.edge_number(edge);
			C[index] = !C[index];
		}
		C_vector[c] = C;
		c++;
	}
	
	//parte 5
	std::vector<bool> C_best;
	int minimo = E;
	for (const auto& C : C_vector) {
		int somma = 0;
		for (const auto& x : C)
			if (x) somma += 1;
		
		if (somma < minimo) {
			minimo = somma;
			C_best = C;
		}
	}
	return C_best;
}

bool prod_scalare_bool(const std::vector<bool>& S, const std::vector<bool>& P) {
	bool value = false;
	for (size_t i=0; i<S.size(); i++) {
		if (S[i] && P[i]) //se sono concordi scambio true/false
			value = !value;
	}
	return value;
}

std::vector<bool> diff_simm_bool(const std::vector<bool>& S,const std::vector<bool>& P) {
	int k = S.size();
	std::vector<bool> D;
	D.resize(k);
	for (int i=0; i<k; i++) {
		D[i] = S[i] ^ P[i]; //diversi -> true; uguali -> false
	}
	return D;
}

std::vector<std::vector<bool>> de_pina(const undirected_graph<int>& G, std::vector<std::vector<bool>>& S) {
	int k = S.size();
	std::vector<std::vector<bool>> B;
	B.resize(k);
	for (int i=0; i<k; i++) {
		std::vector<bool> C = lifting(G, S[i]);
		B[i] = C;
		for (int j=i+1; j<k; j++) {
			if (prod_scalare_bool(C,S[j]))
				S[j] = diff_simm_bool(S[j],S[i]);
		}
	}
	return B;
}
