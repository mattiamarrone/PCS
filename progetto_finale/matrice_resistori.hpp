#pragma once
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include <Eigen/Dense>
#include <set>

Eigen::MatrixXd R_matrix(const undirected_graph<int>& G) {
	std::set<undirected_edge<int>> resistors = G.all_resistors();
	int M = resistors.size(); //numero di resistori
	Eigen::MatrixXd R(M, M);
	R.setZero();
	for (int m=0; m<M; m++) {
		R(m,m) = G.resistor_at(m).peso().second;
	}
	return R;
}