#pragma once
#include <iostream>
#include<utility>
#include <algorithm>

// devo implementare una classe undirected_edge che rappresenta un arco in un grafo
// questa classe deve avere un costruttore che specifica i due nodi conessi dall'arco 
// poi ci devono essere due metodi from() e to() che restituiscono i due nodi
    
template <typename T>
class undirected_edge {
    T from_;
    T to_;
	std::pair<char, double> peso_; //il mio peso associato ad un arco è una coppia che mi fornisce informazioni sul tipo di componenete e il valore in double
public:
    // il costruttore riceve due nodi e subito li ordina in modo che from_ sia sempre minore di to_
    undirected_edge(T from, T to, std::pair<char, double> peso = {'0', 0}) : //peso di default
        from_(std::min(from, to)), 
        to_(std::max(from, to)),
		peso_(peso)
    {}

    // ora definisco i metodi 
    T from() const {return from_;}
    T to() const {return to_;}
	std::pair<char, double> peso() const {return peso_;}

    // ora devo implementare un operatore < affinchè gli archi possano essere ordinabili cioè per stabilire chi viene prima e chi viene dopo, questo è utile per gestire al meglio gli archi quando questi diventano le chiavi di una struttura dati più complessa
    bool operator<(const undirected_edge<T>& other) const {
        if (from_ != other.from_) return from_<other.from_;
        return to_ < other.to_;
    }

    // ora serve un operatore == per confrontare due archi
    bool operator==(const undirected_edge<T>& other) const {      
        return (from_==other.from_ && to_==other.to_);
    }
    };

// infine serve un operatore di stampa <<, che implementiamo fuori dalla classe 
template<typename T>
std::ostream& operator<<(std::ostream& os, const undirected_edge<T>& arco) {
    os << "(" << arco.from() << ", " << arco.to() << ")";
    return os;
}
