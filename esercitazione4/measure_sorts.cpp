#include <iostream>
#include <vector>
#include <algorithm> 
#include <iomanip>  
#include <cstdlib>
#include "sort.hpp"
#include "randfiller.h"
#include "timecounter.h"


int main(){
	randfiller rf;
	timecounter tc;
	std::vector<int> v;
	std::vector<double> bubble;
	std::vector<double> sort_v;
	std::vector<double> insertion;
	std::vector<double> selection;
	bubble.resize(12);
	sort_v.resize(12);
	insertion.resize(12);
	selection.resize(12);
	int n=0;
	for (int i=4;i<=8192;i*=2){
		v.resize(i);
		rf.fill(v,-1000,1000);
		
		std::vector<int> copia_b=v;
		tc.tic();
		bubble_sort(copia_b);
		double bubble_time=tc.toc();
		bubble[n]=bubble_time;
		
		std::vector<int> copia_i=v;
		tc.tic();
		insertion_sort(copia_i);
		double insertion_time=tc.toc();
		insertion[n]=insertion_time;
		
		std::vector<int> copia_se=v;
		tc.tic();
		selection_sort(copia_se);
		double selection_time=tc.toc();
		selection[n]=selection_time;
		
		std::vector<int> copia_s=v;
		tc.tic();
		std::sort(copia_s.begin(),copia_s.end());
		double sort_time=tc.toc();
		sort_v[n]=sort_time;
		n+=1;
	}
	
    std::cout << "N \n";
    int dim = 4;
    for (int j = 0; j < 12; j += 1) {
        std::cout << dim <<",";
        dim *= 2;
    }
    std::cout << "\n";

    std::cout << "Bubble \n";
    for (int j = 0; j < 12; j += 1) {
        std::cout << bubble[j]<< ",";
    }
    std::cout << "\n";

   
    std::cout << "Insertion \n";
    for (int j = 0; j < 12; j += 1) {
        std::cout << insertion[j] << ",";
    }
    std::cout << "\n";

    std::cout << "Selection \n";
    for (int j = 0; j < 12; j += 1) {
        std::cout << selection[j]<< ",";
    }
    std::cout << "\n";

    std::cout << "StdSort \n";
    for (int j = 0; j < 12; j += 1) {
        std::cout << sort_v[j]<< ",";
    }
    std::cout << "\n";
	return 0;
}