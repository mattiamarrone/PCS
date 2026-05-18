#include "graph_visit.hpp"
#include "unidirected_graph2.hpp"
#include <iostream>
#include <queue>
#include <stack>
#include <unordered_map>
#include "lifo.hpp"
#include "fifo.hpp"
#include "recursive_dfs.hpp"
#include "dijkstra.hpp"

int main() {
    unidirected_graph<int> G;
    
    G.add_edge(1, 2);
    G.add_edge(1, 3);
    G.add_edge(1, 4);
	G.add_edge(1, 6);
	G.add_edge(2, 4);
	G.add_edge(2, 5);
	G.add_edge(2, 7);
	G.add_edge(3, 6);
	G.add_edge(4, 6);
	G.add_edge(4, 7);
	G.add_edge(5, 7);
	G.add_edge(6, 7);
	G.add_edge(6, 8);
	G.add_edge(7, 9);
	G.add_edge(8, 9);	

	// bfs
    coda<int> coda_bfs;
    unidirected_graph<int> albero_bfs = graph_visit(G, 1, coda_bfs);
    
    std::cout << "bfs:\n";
   
    
    for (const auto& u : albero_bfs.all_nodes()) {
        for (const auto& v : albero_bfs.neighbours(u)) {
            if (u < v) { // Stampa l'arco una volta sola
                std::cout << u << " -- " << v << ";\n";
               
            }
        }
    }
    
    std::cout << "\n";


	// dfs
    pila<int> pila_dfs;
    unidirected_graph<int> albero_dfs = graph_visit(G, 1, pila_dfs);
    
    std::cout << "dfs: \n";
    
    for (const auto& u : albero_dfs.all_nodes()) {
        for (const auto& v : albero_dfs.neighbours(u)) {
            if (u < v) { // Stampa l'arco una volta sola
                std::cout << u << " -- " << v << ";\n";
            }
        }
    }
    std::cout << "\n";
	
	// recursive_dfs
	unidirected_graph<int> albero_recursive_dfs = recursive_dfs(G,1);
	
	 std::cout << "recursive_dfs: \n";
    
    for (const auto& u : albero_recursive_dfs.all_nodes()) {
        for (const auto& v : albero_recursive_dfs.neighbours(u)) {
            if (u < v) { // Stampa l'arco una volta sola
                std::cout << u << " -- " << v << ";\n";
            }
        }
    }
    std::cout << "\n";
	
	
	// dijkstra
    unidirected_graph<int> albero_dijkstra = dijkstra(G, 1);
    
    std::cout << "dijkstra: \n";    
    for (const auto& u : albero_dijkstra.all_nodes()) {
        for (const auto& v : albero_dijkstra.neighbours(u)) {
            if (u < v) { 
                std::cout << u << " -- " << v << ";\n";
            }
        }
    }
    std::cout << "\n";
	
    return 0;
}