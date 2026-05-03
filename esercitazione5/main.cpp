#include <iostream>
#include <vector>
#include <algorithm> 
#include <iomanip>  
#include <cstdlib>
#include "sort.hpp"
#include "randfiller.h"
#include "timecounter.h"

int main() {
	randfiller rf;
	timecounter tc;
	std::vector<std::vector<double>> tempi(7, std::vector<double>(20));
	int k=0;
	for (int N=5;N<=100;N+=5){
		std::vector<std::vector<int>> test_set(100, std::vector<int>(N));
		for (int i = 0; i < 100; i+=1) {
			rf.fill(test_set[i],-1000,1000); // riempo con numeri casuali
        }
		double tempo_totale;
		
		// BUBBLE
		std::vector<std::vector<int>> dati_bubble = test_set; // copia dei dati
		tc.tic(); // Start timer
		for (int i = 0; i < 100; i+=1) {
			bubble_sort(dati_bubble[i]);
		}
		tempo_totale= tc.toc(); // Stop timer
		double tempo_medio_bubble = (tempo_totale) / 100.0;
		tempi[0][k]=tempo_medio_bubble;
		
		// INSERTION
		std::vector<std::vector<int>> dati_insertion = test_set; // copia dei dati
		tc.tic(); // Start timer
		for (int i = 0; i < 100; i+=1) {
			insertion_sort(dati_insertion[i]);
		}
		tempo_totale= tc.toc(); // Stop timer
		double tempo_medio_insertion = (tempo_totale) / 100.0;
		tempi[1][k]=tempo_medio_insertion;
		
		// SELECTION
		std::vector<std::vector<int>> dati_selection = test_set; // copia dei dati
		tc.tic(); // Start timer
		for (int i = 0; i < 100; i+=1) {
			selection_sort(dati_selection[i]);
		}
		tempo_totale= tc.toc();// Stop timer
		double tempo_medio_selection = (tempo_totale) / 100.0;
		tempi[2][k]=tempo_medio_selection;
		
		//MERGE
		std::vector<std::vector<int>> dati_merge = test_set; // copia dei dati
		tc.tic(); // Start timer
		for (int i = 0; i < 100; i+=1) {
			merge_sort(dati_merge[i],0,dati_merge[i].size()-1);
		}
		tempo_totale= tc.toc();// Stop timer
		double tempo_medio_merge = (tempo_totale) / 100.0;
		tempi[3][k]=tempo_medio_merge;
		
		
		//QUICK
		std::vector<std::vector<int>> dati_quick = test_set; // copia dei dati
		tc.tic(); // Start timer
		for (int i = 0; i < 100; i+=1) {
			quick_sort(dati_quick[i],0, dati_quick[i].size()-1);
		}
		tempo_totale= tc.toc(); // Stop timer
		double tempo_medio_quick = (tempo_totale) / 100.0;
		tempi[4][k]=tempo_medio_quick;
		
		
		// STD::SORT
		std::vector<std::vector<int>> dati_std = test_set;
		tc.tic();
		for (int i = 0; i < 100; i+=1) {
			std::sort(dati_std[i].begin(), dati_std[i].end());
		}
		tempo_totale = tc.toc();
		tempi[5][k] = tempo_totale / 100.0;
		
		
		//hybrid
		std::vector<std::vector<int>> dati_hybrid = test_set; // copia dei dati
		tc.tic(); // Start timer
		for (int i = 0; i < 100; i+=1) {
			hybrid_sort(dati_hybrid[i],0, dati_hybrid[i].size()-1);
		}
		tempo_totale= tc.toc(); // Stop timer
		double tempo_medio_hybrid = (tempo_totale) / 100.0;
		tempi[6][k]=tempo_medio_hybrid;
			
		k+=1;
	}
	std::vector<std::string> nomi_algoritmi = {"Bubble", "Insertion", "Selection", "Merge", "Quick", "std::sort","Hybrid"};
    
    for (int alg = 0; alg < 7; alg += 1) {
        std::cout << "Tempi medi " << nomi_algoritmi[alg] << ": \n[ ";
        for (int i = 0; i < 19; i += 1) {
            std::cout << tempi[alg][i] << ", ";
        }
        std::cout << tempi[alg][19] << "]\n\n";
    }
}
