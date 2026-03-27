#pragma once
#include <iostream>
#include <numeric>
#include <concepts>

template<typename I> requires std::integral<I>
class rational
{
	I num_;
	I den_;
	
private:
	void simplify() {
		if (den_==I{0}){
			return;
		}
		I mcd=std::gcd(num_,den_);
		num_/=mcd;
		den_/=mcd;
		if (den_<I{0}){
			num_*=I{-1};
		den_*=I{-1};
		}
	}
		
	
public:
	/* costruttore di default */
	rational()
		: num_(I{0}), den_(I{1}) 
	{}
	
	/* costruttore user-defined */
	rational(const I& pnum, const I& pden)
		: num_(pnum), den_(pden)
	{
		if (den_ == I{0}) {
			if (num_ < I{0}) {
				num_ = I{-1}; 
			}
			else if(num_ > I{0}) {
				num_ = I{1}; 
			}
		}
		simplify();
	}
	
	
	/* Restituiscono i valori di num e den */
	I num() const{return num_; }
	I den() const{return den_; }
	
	/* Implementazione canonica dell'operatore += */
	rational& operator+=(const rational& other) {
		if ((den_ == I{0} && num_ == I{0}) || (other.den() == I{0} && other.num() == I{0})) {
			num_ = I{0};
			den_ = I{0};
			return *this;
		}
		if (den_ == I{0} || other.den() == I{0}) {
			if (den_ == I{0} && other.den() == I{0} && num_ != other.num()) {
				num_ = I{0};
				den_ = I{0};
				return *this;
			}
			if (other.den() == I{0}) {
				num_ = other.num(); 
				den_ = I{0};
			}
			return *this;
		}
		num_ = (num_ * other.den()) + (other.num() * den_);
		den_ = den_ * other.den();
		simplify();
		return *this;
	}
	
	/* Implementazione canonica della somma */
    rational operator+(const rational& other) const {
        rational ret = *this;
        ret += other;
        return ret;
    }
	
	/* Implementazione canonica dell'operatore -= */
	rational& operator-=(const rational& other) {
		rational opposto(-other.num(), other.den());
		*this += opposto;
		return *this;
	}

	/* Implementazione canonica della sottrazione */
    rational operator-(const rational& other) const {
        rational ret = *this;
        ret -= other;
        return ret;
    }	
	
	/* Implementazione canonica dell'operatore *= */
	rational& operator*=(const rational& other) {
		// se uno dei due è NaN il risultato è NaN
		
		if ((den_ == I{0} && num_ == I{0}) || (other.den() == I{0} && other.num() == I{0})) {
			num_ = I{0};
			den_ = I{0};
			return *this;
		}
		//vediamo gli infiniti
		if (den_ == I{0} || other.den() == I{0}) {
			// 0*inf = NaN
			if ((den_==I{0} && other.num()==I{0}) || (other.den() == I{0} && num_==I{0})){
				num_= I{0};
				den_=I{0};
				return *this;
			}
			if (num_ != I{0} && other.num() != I{0}) {
				// Controlliamo se i segni sono concordi
				if ((num_ > I{0} && other.num() > I{0}) || (num_ < I{0} && other.num() < I{0})) {
					num_ = I{1};
				}
				else { // I segni sono discordi
					num_ = I{-1};
				}
				den_ = I{0};
				return *this;
			}
		}
		num_ = (num_ * other.num());
		den_ = den_ * other.den();
		simplify();
		return *this;
	}
	
	/* Implementazione canonica della moltiplicazione */
    rational operator*(const rational& other) const {
        rational ret = *this;
        ret *= other;
        return ret;
    }	
		
    /* Implementazione canonica dell'operatore /= */
	rational& operator/=(const rational& other) {
		rational reciproco(other.den(), other.num());
		*this *= reciproco;
		return *this;
	}

	/* Implementazione canonica della divisione */
    rational operator/(const rational& other) const {
        rational ret = *this;
        ret /= other;
        return ret;
    }
	
};



template<typename I>
std::ostream&
operator<<(std::ostream& os, const rational<I>& r)
{
	if (r.den()==I{0}){
		if (r.num()== I{0} ){
			os << "NaN" ;
		}
		else if (r.num()== I{-1}){
			os << "-Inf" ;
		}
		else {
			os << "Inf" ;
		}
	}
	else {
		os << r.num() << "/" << r.den() ;
	}
    return os;
}
