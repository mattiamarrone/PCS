#pragma once
#include <iostream>
#include <algorithm> 

template <typename T>
class unidirected_edge {
private:
    T from_;
    T to_;

public:
    // Costruttore impone che from_ < to_ al momento della creazione
    unidirected_edge(T n1, T n2)
        : from_(std::min(n1, n2)), to_(std::max(n1, n2)) {
    }

    // Metodi from() e to()
    T from() const { return from_; }
    T to() const { return to_; }

    
    // opearote <
    bool operator<(const unidirected_edge<T>& other) const {
        
        if (from_ == other.from_) {
            return to_ < other.to_;
        }
        return from_ < other.from_;
    }

    // Operatore di uguaglianza
    bool operator==(const unidirected_edge<T>& other) const {
        return (from_ == other.from_) && (to_ == other.to_);
    }
};

template<typename T>
std::ostream&
operator<<(std::ostream& os, const unidirected_edge<T>& edge){
	os << "{" << edge.from_ << ", " << edge.to_ << "}";
	return os;
}
