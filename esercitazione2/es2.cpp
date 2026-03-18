#include <iostream>
#include <cmath>
#include <algorithm>

int main()
{
static const int N = 10;
double arr[N] = {10.2 , 0.1, 3.3, 0.4, 4.6, 2.6, 5.7, 2.1, 2.3, 5.3};
double min_arr = arr[0];
double max_arr = arr[0];
double sum = 0;
double sums= 0;
for (int i=0; i<N; i+=1) {
	min_arr = std::min(min_arr , arr[i]);
	max_arr = std::max(max_arr , arr[i]);
	sum = sum +arr[i];
}
std::cout <<"the min is: " << min_arr << "\n";
std::cout <<"the max is: " << max_arr << "\n";
double mean = sum/N;
std::cout << "the mean is: " << mean << "\n";
for (int i=0; i<N; i+=1) {
	sums =sums + (arr[i]-mean)*(arr[i]-mean);
}
double var = sums/N;
double devst = sqrt(var);
std::cout << "the standard deviation is: "<< devst << "\n";

return 0;
}