#pragma once

#include<list>
template<typename T>
class coda{
private:

	std::list<T> coda_;
public:

	//costruttoredi default
	coda()=default;
	
	// metodo put()
	void put(const T& elemento){
		coda_.push_front(elemento);
	}	
	// metodo get()
	T get(){
		T last=coda_.back();
		coda_.pop_back();
		return last ;
	}

	// metodo empty()
	bool empty() const{
		return coda_.empty();
	}
};