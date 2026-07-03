#include "lettura_file.hpp"
#include "undirected_graph.hpp"
#include "undirected_edge.hpp"
#include <iostream>
#include <vector>
#include <set>
#include <Eigen/Dense>
#include "cicli_minimi.hpp"
#include "dfs_non_minimi.hpp"
#include "matrice_resistori.hpp"
#include "matrice_incidenza.hpp"
#include "calcolo_correnti.hpp"
#include <string>
#include "tensioni_generatori.hpp"
#include "graph_visit.hpp"
#include "lifo.hpp"
#include <chrono>


int main(int argc, char* argv[]) {
	
    if (argc != 2) { //controllo che user abbia specificato solo il nome del file
        std::cerr << "Errore: numero di parametri errato.\n";
        return 1; 
    }
    std::string filename = argv[1]; // nome del file 

    auto [grafo, mappa_resistenze] = lettura_file(filename);

    if (grafo.all_edges().size() == 0) { // se ci sono problemi nell'apertura del grafo oppure è un circuito vuoto
        std::cerr << "Errore: Rete vuota o file non valido.\n";
        return 2;
    }
	
	std::cout << "      Nodi: " << grafo.all_nodes().size() << ", Archi: " << grafo.all_edges().size() << "\n";	
	
	

	Eigen::MatrixXd R = R_matrix(grafo); // matrice R 
	std::vector<std::vector<bool>> v_incidenza = vettori_incidenza(grafo);

	// METODO DE PINA (CICLI MINIMI)

	auto start_depina = std::chrono::high_resolution_clock::now(); //

	std::vector<std::vector<int>> cicli = cicli_minimi(grafo, v_incidenza); // Recuperiamo i cicli reali
	Eigen::MatrixXd B = B_matrix(grafo, cicli); // matrice B 
	Eigen::VectorXd v_maglie = tensioni_generatori(grafo, cicli); // Calcoliamo v_maglie direttamente dai cicli 
	int n_maglie = cicli.size(); 
	Eigen::VectorXd x0 = Eigen::VectorXd::Zero(n_maglie); // Vettore iniziale 
	Eigen::VectorXd i = calcolo_correnti(R, B, v_maglie, x0);
	Eigen::VectorXd V = R * B * i; 
	Eigen::VectorXd I = B * i;     

	auto end_depina = std::chrono::high_resolution_clock::now();
	auto duration_depina = std::chrono::duration_cast<std::chrono::microseconds>(end_depina - start_depina).count();


	// METODO DFS (CICLI NON MINIMI)

	auto start_dfs = std::chrono::high_resolution_clock::now(); 

	pila<int> pila_di_supporto; // creo una pila di supporto per la visita del grafo
	int nodo_sorgente=*grafo.all_nodes().begin(); // prendo il primo nodo del grafo come nodo sorgente
	undirected_graph<int> albero_T=graph_visit(grafo, nodo_sorgente, pila_di_supporto);              // calcoliamo l'albero T con DFS
	std::vector<std::vector<int>> cicli_dfs = calcola_tutti_i_cicli_dfs(grafo, albero_T); // questi sono i cicli con dfs non minimi
	Eigen::MatrixXd B_dfs = B_matrix(grafo, cicli_dfs); // matrice B con DFS 
	Eigen::VectorXd v_maglie_dfs=tensioni_generatori(grafo, cicli_dfs); // calcoliamo v_maglie direttamente dai cicli DFS
	int n_maglie_dfs=cicli_dfs.size();
	Eigen::VectorXd x0_dfs=Eigen::VectorXd::Zero(n_maglie_dfs); 
	Eigen::VectorXd i_dfs = calcolo_correnti(R, B_dfs, v_maglie_dfs, x0_dfs);
	Eigen::VectorXd V_dfs = R * B_dfs * i_dfs; 
	Eigen::VectorXd I_dfs = B_dfs * i_dfs;     

	auto end_dfs = std::chrono::high_resolution_clock::now();
	auto duration_dfs = std::chrono::duration_cast<std::chrono::microseconds>(end_dfs - start_dfs).count();

	std::cout<<"Risultati con De Pina: \n\n";
	int k = 0;
	for (const auto& [arco, id] : mappa_resistenze)	{
		std::cout << "R" << id << " V = " << V[k] << " volts, I = " << I[k] << " amps.\n";
		k++; 
	}


	std::cout<<"Risultati con DFS: \n\n";
	k=0; // dobbiamo resettare k a zero per ciclare di nuovo
	for (const auto& [arco, id] : mappa_resistenze)	{
		std::cout << "R" << id << " V = " << V_dfs[k] << " volts, I = " << I_dfs[k] << " amps.\n";
		k++; 
	}
	
	std::cout << "\n";
	std::cout << "Tempo di De Pina: " << duration_depina << " microsecondi.\n";
	std::cout << "\n";
	std::cout << "Tempo di DFS: " << duration_dfs << " microsecondi.\n";
	
    return 0;
}