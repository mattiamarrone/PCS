#pragma once
#include "de_pina.hpp"
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include "recursive_dfs.hpp"
#include <vector>
#include <set>

std::vector<std::vector<bool>> vettori_incidenza(const undirected_graph<int>& G) {
	int E = G.all_edges().size(); //numero di archi
	
	//inizializzazione dei vettori S che servono per de_pina
	undirected_graph<int> T = recursive_dfs(G,*G.all_nodes().begin());
	undirected_graph<int> C = G-T;
	int K = C.all_edges().size(); //numero archi del coalbero C
	//numero archi del coalbero == numero cicli fondamentali
	
	std::vector<std::vector<bool>> S;
	S.resize(K);
	int index = 0;
	for (auto& S_i : S) {
		S_i = std::vector<bool>(E, false);
		for (int e=index; e<E; e++) {
			undirected_edge edge = G.edge_at(e);
			if (C.all_edges().count(edge) > 0) { //restituisce 0 se non c'è , 1 se l'edge è presente
				S_i[e] = true;
				index = e+1;
				break;
			}
		}
	}
	
	//calcolo dei vettori d'incidenza con de_pina
	return de_pina(G,S);
}


std::vector<std::vector<int>> cicli_minimi(const undirected_graph<int>& G, const std::vector<std::vector<bool>>& v_incidenza) {
	std::set<undirected_edge<int>> archi = G.all_edges();
	int N = v_incidenza.size(); //numero di cicli
	
	std::vector<std::vector<int>> cicli_ordinati;
	cicli_ordinati.resize(N);
	
	for (int n=0; n<N; n++) {
		//v_incidenza[n] è il vettore di incidenza n-esimo
		
		std::vector<int> ciclo_vec;
		
		std::set<int> ciclo_non_ordinato;
		for (size_t v=0; v<v_incidenza[n].size(); v++) {
			//salvo i numeri di arco del ciclo
			if (v_incidenza[n][v]) {
				ciclo_non_ordinato.insert(v);
			}
		}
		
		int edgeN_starter = *ciclo_non_ordinato.begin();
		ciclo_non_ordinato.erase(ciclo_non_ordinato.begin());
		undirected_edge<int> arco = G.edge_at(edgeN_starter);
		int inizio = arco.from();
		int next = arco.to();
		ciclo_vec.push_back(inizio);
		ciclo_vec.push_back(next);
		
		while (!ciclo_non_ordinato.empty()) {
			bool trovato = false;
			for (const auto& vicino:G.neighbours(next)) {
				undirected_edge<int> edge(next,vicino);
				int edgeN = G.edge_number(edge);
				if (ciclo_non_ordinato.count(edgeN)) {
					ciclo_non_ordinato.erase(edgeN);
					ciclo_vec.push_back(vicino);
					next = vicino;
					trovato = true;
					break;
				}
				if (trovato) break;
			}
		}
		
		cicli_ordinati[n] = ciclo_vec;
	}
	
	return cicli_ordinati;
}