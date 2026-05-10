#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <set>

#include "unidirected_graph.hpp"
#include "unidirected_edge.hpp"

int main() {
    // test 1 base sugli interi
    unidirected_graph<int> g_int;
    // controllo inizializzazione vuota
    if (!g_int.all_nodes().empty()) return EXIT_FAILURE;
	
    // inserimento archi
    if (g_int.add_edge(1, 2) == false) return EXIT_FAILURE;
    if (g_int.add_edge(2, 3) == false) return EXIT_FAILURE;
    if (g_int.add_edge(3, 4) == false) return EXIT_FAILURE;

    // test rigetto duplicati (stesso arco e arco invertito)
    if (g_int.add_edge(1, 2) == true) return EXIT_FAILURE;
    if (g_int.add_edge(2, 1) == true) return EXIT_FAILURE;

    // test esplorazione vicini
    std::set<int> vicini_2 = g_int.neighbours(2);
    if (vicini_2.size() != 2) return EXIT_FAILURE;
    if (vicini_2.find(1) == vicini_2.end()) return EXIT_FAILURE;
    if (vicini_2.find(3) == vicini_2.end()) return EXIT_FAILURE;

    // Test vicini nodo inesistente
    std::set<int> vicini_fantasma = g_int.neighbours(99);
    if (!vicini_fantasma.empty()) return EXIT_FAILURE;


    // test 2 indicizzazione 
    unidirected_edge<int> arco_zero(1, 2);
    unidirected_edge<int> arco_falso(9, 9);

    if (g_int.edge_number(arco_zero) != 0) return EXIT_FAILURE;
    // mi aspetto -1 per arco inesistente
    if (g_int.edge_number(arco_falso) != -1) return EXIT_FAILURE; 

    // recupero per ID
    unidirected_edge<int> rec_arco = g_int.edge_at(0);
    if (rec_arco.from() != 1 || rec_arco.to() != 2) return EXIT_FAILURE;

    // recupero ID inesistente (mi aspetto l'arco sentinella 0,0)
    unidirected_edge<int> rec_sentinella = g_int.edge_at(99);
    if (rec_sentinella.from() != 0 || rec_sentinella.to() != 0) return EXIT_FAILURE;


    
	// test 3 sottrazione
    unidirected_graph<int> g_int_b;
    g_int_b.add_edge(2, 3); // in comune
    g_int_b.add_edge(5, 6); // solo in b

    std::set<unidirected_edge<int>> differenza = g_int - g_int_b;
    
    // in g_int avevamo (1,2), (2,3), (3,4). Tolto (2,3), devono restarne 2
    if (differenza.size() != 2) return EXIT_FAILURE;


    // test 4 grafo di stringhe
    unidirected_graph<std::string> g_str;

    if (g_str.add_edge("Torino", "Milano") == false) return EXIT_FAILURE;
    if (g_str.add_edge("Milano", "Roma") == false) return EXIT_FAILURE;
    if (g_str.add_edge("Milano", "Torino") == true) return EXIT_FAILURE; // duplicato

    std::set<std::string> vicini_milano = g_str.neighbours("Milano");
    if (vicini_milano.size() != 2) return EXIT_FAILURE;

    // il costruttore di default di std::string crea stringhe vuote ""
    
    unidirected_edge<std::string> sentinella_str = g_str.edge_at(999);
    if (sentinella_str.from() != "" || sentinella_str.to() != "") return EXIT_FAILURE;
    // tutti gli if sono stati superati senza innescare EXIT_FAILURE
	
    std::cout << "Tutti i test superati con successo.\n";
    return EXIT_SUCCESS;
}