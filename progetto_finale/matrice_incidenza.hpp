#pragma once
#include "undirected_edge.hpp"
#include "undirected_graph.hpp"
#include "cicli_minimi.hpp"
#include <Eigen/Dense>
#include <vector>
#include <set>

Eigen::MatrixXd B_matrix(const undirected_graph<int>& G, const std::vector<std::vector<int>>& cicli) {
	int M = G.all_resistors().size(); //numero di resistori
	int N = cicli.size();  //numero di cicli
    Eigen::MatrixXd B(M, N);
	B.setZero();
	
	for (int n=0; n<N; n++) {
		std::vector<int> ciclo = cicli[n];
		for (size_t c=0; c<ciclo.size()-1; c++) {
			int nodo1 = ciclo[c];
			int nodo2 = ciclo[c+1];
			if (G.get_weight(nodo1, nodo2).first != 'R') continue;
			
			int m = G.resistor_number(nodo1, nodo2);
			if (m == -1) {
				std::cerr << "resistore non trovato\n";
				continue;
			}
			if (nodo1 < nodo2) B(m,n) = 1;
			else B(m,n) = -1;
		}
	}
	return B;
}

