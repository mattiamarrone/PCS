#include "razionali.hpp"
#include <iostream>

int main() {
	// testo funzioni base
    std::cout << "Standard (1/2): " << rational<int>(1, 2)<< "\n";
    std::cout << "Riduzione (4/8): " << rational<int>(4, 8)<< "\n" ;
    std::cout << "Segno al den (1/-2): " << rational<int>(1, -2)<< "\n" ;
    std::cout << "Doppio segno (-3/-4): " << rational<int>(-3, -4)<< "\n" ;
    std::cout << "Zero (0/5): " << rational<int>(0, 5) << std::endl;
	// testo come gestisce inf e NaN
    rational<int> inf(5, 0);
    rational<int> n_inf(-5, 0);
    rational<int> nan(0, 0);
    std::cout << "Infinito positivo (5/0): " << inf << "\n";
    std::cout << "Infinito negativo (-5/0): " << n_inf << "\n";
    std::cout << "Not a Number (0/0): " << nan << "\n";
	// testo operazioni nel caso ben definito
    rational<int> a(1, 2);
    rational<int> b(1, 3);
    std::cout << "1/2 + 1/3 = " << (a + b) << "\n";
    std::cout << "1/2 - 1/3 = " << (a - b) << "\n";
    std::cout << "1/2 * 1/3 = " << (a * b) << "\n";
    std::cout << "1/2 / 1/3 = " << (a / b) << "\n";
	// testo operazioni nel caso inf e NaN
    std::cout << "Razionale + Inf: " << (a + inf) << "\n";
    std::cout << "Inf + Inf: " << (inf + inf) << "\n";
    std::cout << "Inf - Inf (NaN atteso): " << (inf - inf) << "\n";
    std::cout << "Inf * Razionale > 0: " << (inf * a) << "\n";
    std::cout << "Inf * Razionale < 0: " << (inf * rational<int>(-1, 2)) << "\n";
    std::cout << "Inf * 0 (NaN atteso): " << (inf * rational<int>(0, 1)) << "\n";
    std::cout << "Razionale / Inf: " << (a / inf) << "\n";
    
 
    std::cout << "NaN + 1/2: " << (nan + a) << "\n";
    std::cout << "NaN * Inf: " << (nan * inf) << "\n";

    return 0;
}