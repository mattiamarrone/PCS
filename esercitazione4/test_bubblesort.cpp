#include <iostream>
#include <vector>
#include <string>
#include "randfiller.h"
#include <cstdlib>
#include "sort.hpp"

int main() {
	std::vector<std::string> stringa={"calcetto","politecnico","programmazione","matlab","tavolino","laurea","tutorato","esercitazione","30L","18"};
	bubble_sort(stringa);
	if (is_sorted(stringa)==false){
		return EXIT_FAILURE;
	}
	randfiller rf;
	//vettore generico per le dimensioni//
    std::vector<int> di;
    di.resize(100);
    rf.fill(di, 0, 10000); 
    for (int i=0;i<100;i+=1){
		std::vector<int> vi;
		vi.resize(di[i]);
		rf.fill(vi, -1000,1000 );

		std::vector<float> vf;
		vf.resize(di[i]);
		rf.fill(vf, -1000.5f, 1000.5f);
	
		std::vector<double> vd;
		vd.resize(di[i]);
		rf.fill(vd, -1000.5, 1000.5);
		
		bubble_sort(vi);
		bubble_sort(vf);
		bubble_sort(vd);
		if (is_sorted(vi)==false ||is_sorted(vd)==false||is_sorted(vf)==false  ){
		return EXIT_FAILURE;
		}	
	}

	return EXIT_SUCCESS;
}