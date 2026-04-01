#include <vector>

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

 
