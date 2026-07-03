#pragma once
#include "undirected_graph.hpp"
#include "cicli_minimi.hpp"
#include <Eigen/Dense>
#include <vector>

Eigen::VectorXd tensioni_generatori(const undirected_graph<int>& G, const std::vector<std::vector<int>>& cicli) {
    int N = cicli.size();
    Eigen::VectorXd v_maglie(N);
    v_maglie.setZero();

    for (int n = 0; n < N; n++) {
        const std::vector<int>& ciclo = cicli[n];
        double somma_tensioni = 0.0;

        for (size_t c = 0; c < ciclo.size() - 1; c++) {
            int nodo1 = ciclo[c];
            int nodo2 = ciclo[c+1];

            // Se l'arco non è un generatore di tensione, lo salta
            if (G.get_weight(nodo1, nodo2).first != 'V') continue;

            double valore = G.get_weight(nodo1, nodo2).second;

           
            if (nodo1 < nodo2) {
                somma_tensioni -= valore;
            } else {
                somma_tensioni += valore;
            }
        }
        v_maglie(n) = somma_tensioni;
    }

    return v_maglie;
}




