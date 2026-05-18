#pragma once

#include<list>
template<typename T>
class pila{
private:

	std::list<T> pila_;
public:

	//costruttoredi default
	pila()=default;
	
	// metodo put()
	void put(const T& elemento){
		pila_.push_back(elemento);
	}
	// metodo get()
	T get(){
		T last=pila_.back();
		pila_.pop_back();
		return last;
	}
		
	// metodo empty()
	bool empty() const{
		return pila_.empty();
	}
};