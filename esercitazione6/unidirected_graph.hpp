#pragma once

#include<set>
#include<map>
#include<list>
#include<unordered_map>
#include<algorithm>

#include "unidirected_edge.hpp"
template<typename T>
class unidirected_graph {
private:
	// per trovare subito nodi e vicini
    std::map<T, std::set<T>> adj_list_;
    // insieme degli archi
    std::set<unidirected_edge<T>> edges_;
    // indicizzazione
    int next_edge_id_;
    std::map<unidirected_edge<T>, int> edge_to_id_;
    std::unordered_map< int, unidirected_edge<T>> id_to_edge_;
public:

	// costruttore di default //
	unidirected_graph() 
		: next_edge_id_(0) {
	}
	
	// costruttore di copia //
	unidirected_graph(const unidirected_graph<T>& other)
		: adj_list_(other.adj_list_),
		edges_(other.edges_),
		next_edge_id_(other.next_edge_id_),
		edge_to_id_(other.edge_to_id_),
		id_to_edge_(other.id_to_edge_){
	}
	
	// neighbours //
	std::set<T> neighbours(const T& node) const {
		auto itor = adj_list_.find(node);
		// Se l'iteratore non punta alla fine della mappa, il nodo esiste
		if (itor != adj_list_.end()) {
			return (*itor).second; // itor->second è il valore (il set di vicini)
		}
		// Se il nodo non è presente nel grafo, restituisce un std::set vuoto
		return std::set<T>(); 
	}
	
	// add_edge()
	
	bool add_edge(const T& u, const T& v) {
		unidirected_edge<T> nuovo_arco(u, v);
		auto ris = edges_.insert(nuovo_arco);
		if (ris.second == true) {
			adj_list_[u].insert(v);
			adj_list_[v].insert(u);
			edge_to_id_.insert({nuovo_arco, next_edge_id_});
			id_to_edge_.insert({next_edge_id_, nuovo_arco});
			next_edge_id_++;

			return true;
		}
		return false;
	}
	
	// all_edges()
	const std::set<unidirected_edge<T>>& all_edges() const {
    return edges_;
	}
	
	// all_nodes()
	std::set<T> all_nodes() const {
		std::set<T> nodes;
		for (const auto& [node, neighbors] : adj_list_) {
			
			nodes.insert(node);
		}
		return nodes;
	}
	
	// edge_number()
	int edge_number(const unidirected_edge<T>& edge) const{
		auto it=edge_to_id_.find(edge);
		if (it!=edge_to_id_.end()){ // se l'arco esiste nel grafo
			return it->second;
		}
		else {
			std::cerr << "Errore: l'arco richiesto non e' presente nel grafo.\n";
			return -1; // se non esiste l'arco restituisco id -1
		}
	}

	// edge_at()
    unidirected_edge<T> edge_at(int id ) const{
		auto it=id_to_edge_.find(id);
		if(it!= id_to_edge_.end()){ // se l'id è valido
			return it->second;
		}
		else {
			std::cerr << "Errore: ID non valido. Restituisco arco sentinella.\n";
			return unidirected_edge<T>(T{},T{}); // restituisco arco nullo, se T ha un costruttore di default
		}
	}
	
	// operator-() sottrazione di G-G'
	std::set<unidirected_edge<T>> operator-(const unidirected_graph<T>& other) const {
		std::set<unidirected_edge<T>> result;
		std::set_difference( // usiamo set_difference() perchè sono set già ordinati e invece di avere O(NlogN') così ho O(n+N')
			this->edges_.begin(), this->edges_.end(), // G
			other.edges_.begin(), other.edges_.end(), // G'
			std::inserter(result, result.begin()) // per inserire i risultati in modo corretto
		);
		return result;
	}
};
		
		