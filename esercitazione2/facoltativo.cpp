#include <iostream>

int main()
{
	double arr[10]={10,9,8,7,6,5,4,3,2,1};
	bool flag1=false;
	while (flag1 == false) {
		bool flag2=false;
		for (int i=0;i<9;i+=1) {
			if (arr[i]>arr[i+1]) {
				double n = arr[i];
				arr[i]=arr[i+1];
				arr[i+1]=n;
				flag2=true;
			}
		}
		if (flag2==false){
			flag1=true;
		}
	}
std::cout << " the sorted array is: { " ;
for (int i=0; i<9; i+=1) {
	std::cout << arr[i]<< ", " ;	
}
std::cout<< arr[9] << " } \n";

return 0;
}