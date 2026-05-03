#pragma once
#include <vector>
#include <cmath>
#include <limits>
#include <algorithm>
template<typename T>
// funzione is_sorted() //
bool is_sorted(const std::vector<T>& vec) {
	int n=vec.size();
	if (n<=1){
		return true;
	}
	for(int i=0; i<(n-1);i+=1){
		if (vec[i]>vec[i+1]) {
			return false;
		}
	}
	return true;
}


//merge //
template<typename T>
void merge(std::vector<T>& A, int p, int q, int r) {
	int n1=q-p+1;
	int n2=r-q;
	std::vector<T> L(n1+1);
	std::vector<T> R(n2+1);
	for (int i=0; i<n1; i+=1) {
		L[i]=A[p+i];
	}
	for (int j=0; j<n2; j+=1) {
		R[j]=A[q+j+1];
	}
	int i=0;
	int j=0;
	int k=p;
	while(i<n1 && j<n2) {
		if (L[i]<=R[j]) {
			A[k]=L[i];
			i+=1;
		}
		else {
			A[k]=R[j];
			j+=1;
		}
		k+=1;
	}
	// Se rimangono elementi in L 
    while (i < n1) {
        A[k] = L[i];
        i += 1;
        k += 1;
    }
    // Se rimangono elementi in R
    while (j < n2) {
        A[k] = R[j];
        j += 1;
        k += 1;
    }
}

// merge_sort //
template<typename T>
void merge_sort(std::vector<T>& A, int p, int r) {
	if (p<r){
		int q= p+(r-p)/2;
		merge_sort(A,p,q);
		merge_sort(A,q+1,r);
		merge(A,p,q,r);
	}
}


// partition //
template<typename T>
int partition(std::vector<T>& A, int p, int r){
	T x=A[r];
	int i=p-1;
	for (int j=p; j<r;j+=1){
		if(A[j]<=x){
			i=i+1;
			std::swap(A[i],A[j]);
		}
	}
	std::swap(A[i+1],A[r]);
	return i+1;
}
// quick_sort //
template<typename T>
void quick_sort(std::vector<T>& A, int p, int r) {
	if (p<r) {
		int q = partition(A,p,r);
		quick_sort(A,p,q-1);
		quick_sort(A,q+1,r);
	}
}

		
// bubble_sort //
template<typename T>
void bubble_sort(std::vector<T>& A){
	int n=A.size();
	if(n<=1){
		return;
	}
	for (int i=0; i< (n-1);i+=1){
		for (int j=n-1; j>=i+1;j-=1) {
			if(A[j]<A[j-1]){
				T temp=A[j];
				A[j]=A[j-1];
				A[j-1]=temp;
			}
		}
	}
}
//insertion_sort//
template<typename T>
void insertion_sort(std::vector<T>& A){
	int n=A.size();
	if(n<=1){
		return;
	}
	for (int j=1; j< n;j+=1){
		T key=A[j];
		int i=j-1;
		while (i>=0 && A[i]>key){
			A[i+1]=A[i];
			i=i-1;
		}
	A[i+1]=key;
	}
}
//selection_sort//
template<typename T>
void selection_sort(std::vector<T>& A){
	int n=A.size();
	if(n<=1){
		return;
	}
	for ( int i =0; i<n-1;i+=1){
		int min=i;
		for (int j=i+1;j<n;j+=1){
			if(A[j]<A[min]){
				min=j;
			}
		}
		T temp=A[i];
		A[i]=A[min];
		A[min]=temp;		
	}
}

const int soglia = 45;
//quick_sort_ibrido
template<typename T>
void hybrid_sort(std::vector<T>& A, int p, int r) {
	if(r-p+1 <= soglia){
		insertion_sort(A);
		return ;
	}
	if (p<r) {
		int q = partition(A,p,r);
		quick_sort(A,p,q-1);
		quick_sort(A,q+1,r);
	}
}


