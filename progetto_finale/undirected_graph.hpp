#pragma once
#include <iostream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <utility>
#include "undirected_edge.hpp"


// ora devo implementare una classe undirected_graph, conterrà una lista di nodi e una lista di archi 
template <typename T>
class undirected_graph {
    private:
        // per ogni nodo consideriamo la sua lista di adiacenza cioè la lista dei suoi vicini
        // per rappresentarla utilizzo una mappa, la chiave è il nodo mentre il valore è un set che contiene i nodi adiacenti
        std::unordered_map<T, std::set<T>> lista_adiacenza_;

        // poi mi servirà un insieme di archi salvato come un set, preferisco i set così da eliminare i duplicati
        std::set<undirected_edge<T>> archi_;

    public:
        // implemento il costruttore di default
        undirected_graph()=default; 

        // ora implemento il metodo neighbours() che dato un nodo restituisce la lista dei suoi vicini
        // l'idea è quella di restituire un set che contiene i nodi adiacenti al nodo in questione
        std::set<T> neighbours(const T& nodo) const {
            auto iteratore = lista_adiacenza_.find(nodo);  // cioè cerco il nodo nella lista di adiacenza, il metodo find restituisce un iteratore: se il nodo è presente nella lista di adiacenza allora l'iteratore punta alla posizione del nodo, altrimento l'iteratore punterà alla fine della lista di adiacenza
            if (iteratore != lista_adiacenza_.end()) {
                return iteratore->second;
            }                                        // cioè se il nodo è presente nella lista di adiacenza allora restituisco sotto forma di set tutti i suoi vicini che sono contenuti nella parte "second" dell'iteratore 
            return std::set<T>();                    // se non trovo il nodo nella lista di adiacenza allora restuisco un set vuoto
        }
            

        // ora implemento il metodo add_edge() che dato un arco lo aggiunge al grafo
        // cioè praticamente chiamo due nodi e aggiungo l'uno alla lista di adiacenza dell'altro, infine aggiungo l'arco alla lista di tutti gli archi del grafo
        // avendo usato un set come struttura dati non mi devo nemmeno preoccupare di aver inseito più volte lo stesso arco
        void add_edge(const T& nodo1,const T& nodo2, const std::pair<char, double>& peso = {'0', 0}) {
            undirected_edge<T> arco(nodo1, nodo2, peso); // come prima cosa creo un arco tra i due nodi che prendo in input
            lista_adiacenza_[nodo1].insert(nodo2);  // aggiorno la lista di adiacenza del nodo 1
            lista_adiacenza_[nodo2].insert(nodo1);  // aggiorno la lista di adiacenza del nodo 2
            archi_.insert(arco);                    // come ultima cosa aggiungo l'arco appena creato al set di archi del grafo
        }
		
		
		// questo metodo servirà per restituire il peso associato ad un arco, specificando solo i due nodi che lo compongono
		std::pair<char, double> get_weight(const T& nodo1, const T& nodo2) const{
			T from = std::min(nodo1, nodo2); // mi assicuro di creare un arco correttamente
			T to =std::max(nodo1, nodo2);
			
			for(const auto& arco : archi_){ // itero su tutti gli archi del mio grafo per cercare quello che va da from a to. N:B nel mio progetto non ha senso parlare di archi equivalenti perchè non consideriamo resistenze in parallelo. Altrimenti potrei assegnare un peso sbagliato di un arco che ha setesso inizio e fine ma peso diverso.
				if(arco.from() == from && arco.to() == to){ // condizione di equivalenza
					return arco.peso(); // uso il metodo di undirected_edge
				}
			}
			return {'0', 0.0};
		}		

		// ora implemento il metodo all_resistors() che restituisce tutti le resistenze del grafo
		std::set<undirected_edge<T>> all_resistors() const{
			std::set<undirected_edge<T>> resistori_totali;
			for (const auto& arco : archi_) {
				if (arco.peso().first == 'R')
					resistori_totali.insert(arco);          // inserisco in archi_totali gli archi che contengono resistori (componente 1 del peso = 'R')
            }
            return resistori_totali;
		}
		
		
        // ora implemento il metodo all_edges() che restituisce tutti gli archi del grafo
        std::set<undirected_edge<T>> all_edges() const {
            return archi_;
        }

        
        // ora implemento il metodo all_nodes() che resituisce la lista di tutti i nodi del grafo
        // itero sulla lista di adiacenza e prendo tutte le chiavi che rappresentano i nodi 
        // forse è meglio restiuire un set invece di un vettore così da evitare ripetizioni
        std::set<T> all_nodes() const {
            std::set<T> nodi_totali;                         // creo un set che conterrà tutti i nodi del grafo
            for (const auto& coppia : lista_adiacenza_) {
                nodi_totali.insert(coppia.first);            // inserisco in nodi_totali la prima parte della coppia nella lista di adiacenza
            }
            return nodi_totali;
        }


        // ora implemento il metodo edge_number() che dato un arco ne restiuisce la sua numerazione all'interno del grafo
        int edge_number(const undirected_edge<T>& arco) const {
            int numero_arco=0;                                            // assegno il numero 0 al primo arco del grafo
            for (const auto& arco_corrente : archi_) {     // itero su titti gli archi del grafo 
                if (arco_corrente.from() == arco.from() && arco_corrente.to() == arco.to()) {
                    return numero_arco;         // se l'arco corrente e di input hanno gli stessi estremi, allora restituisco il numero dell'arco corrente
                }
                numero_arco = numero_arco+1;                            // altrimenti vado avanti e incremento il numero dell'arco corrente
            }
            return -1;                                                    // se in input do un arco che non è presente nel grafo allora restituisco -1
        }
		
		//metodo analogo a edge_number() per i resistori
		int resistor_number(const T& nodo1, const T& nodo2) const {
            int numero_resistore=0;
			T from = std::min(nodo1, nodo2); // mi assicuro di creare un arco correttamente
			T to =std::max(nodo1, nodo2);
			
            for (const auto& resistore_corrente : this->all_resistors()) {
                if (resistore_corrente.from() == from && resistore_corrente.to() == to) {
                    return numero_resistore;
                }
                numero_resistore = numero_resistore+1;
            }
            return -1;
        }

        // ora implemento il metodo edge_at() che dato un numero d'arco restituisce il corrispondente oggetto arco all'interno del grafo
        undirected_edge<T> edge_at(int numero_arco) const{
            int numero_arco_corrente=0;                                   // assegno il numero 0 al primo arco del grafo
            for (const auto& arco_corrente : archi_) {     // itero su tutti gli archi del grafo}
                if (numero_arco_corrente == numero_arco)   {
                    return arco_corrente;              // se il numero dell'arco corrente è uguale al numero dell'arco che prendo in input allora restituisco l'arco corrente
                }
                numero_arco_corrente = numero_arco_corrente+1;
            }
			return undirected_edge<T>(T{}, T{}, {'0', 0.0});
        }
		
		//metodo analogo a edge_at() per i resistori
		undirected_edge<T> resistor_at(int numero_resistore) const{
            int numero_resistore_corrente=0;
            for (const auto& resistore_corrente : this->all_resistors()) {
                if (numero_resistore_corrente == numero_resistore)   {
                    return resistore_corrente;
                }
                numero_resistore_corrente = numero_resistore_corrente+1;
            }
			return undirected_edge<T>(T{}, T{}, {'0', 0.0});
        }
        
        // ora implementiamo l'opratore differenza operator-() che permette di calcolare la differenza tra due grafi
        // cioè dati due grafi G1 e G2 , la differenza G1-G2 è data da un nuovo grafo che contiene tutti i nodi di G1 e tutti gli archi
        // di G1 che però non sono presenti in G2
        undirected_graph<T> operator-(const undirected_graph<T>& other) const {
            undirected_graph<T> grafo_differenza;            // creoo un nuovo grafo che sarà il grafo differenza

            // la prima cosa che faccio è che mi assicuro che tutti i nodi di G1 siano nel grafo differenza
            for (const auto& nodo : this->all_nodes()) {
                grafo_differenza.lista_adiacenza_[nodo];      // credo il nodo anche se è isolato
            }

            std::vector<undirected_edge<T>> archi_differenza;     // creo un set che conterrà tutti gli archi di G1 che non sono presenti in G2
            std::set_difference(archi_.begin(), archi_.end(), other.archi_.begin(), other.archi_.end(), 
            std::back_inserter(archi_differenza));              // qui uso la set_difference per calcolare la differenza tra gli archi

            for (const auto& arco : archi_differenza) {
                grafo_differenza.add_edge(arco.from(), arco.to(), arco.peso());    // aggiungo al grafo differenza gli archi presenti in G1 ma non in G2
            }

            return grafo_differenza; 
        }
};
