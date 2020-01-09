#include<math.h>
#include <iostream>
using namespace std;

double one_term_of_sum(int ii, int iN){
	double term = 1/(1 + pow((ii - .5)/double(iN), 2.));
	return term;
}

int main(){

	// Initial value
	int N = 840;
	
	// Actual pi approximation
	double pi_estimate = 0.;
	for (int i = 1; i < N + 1; i++){
		pi_estimate += one_term_of_sum(i, N);
	}
	pi_estimate = pi_estimate*(4./N);

	// Printing the result
	cout.precision(20);
	std::cout << pi_estimate << std::endl;
	return 0;
}