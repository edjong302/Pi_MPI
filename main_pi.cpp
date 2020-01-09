#include<math.h>
#include <iostream>
#include <mpi.h>
using namespace std;

double one_term_of_sum(int ii, int iN){
	double term = 1/(1 + pow((ii - .5)/double(iN), 2.));
	return term;
}

int main(int argc, char** argv){
	MPI_Init(NULL, NULL);

	// Initial value
	int N = 840;
	int size, rank;
	MPI_Comm comm;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	comm = MPI_COMM_WORLD;

	int n = N/size;
	
	// Actual pi approximation
	double pi_estimate_part = 0.;
	for (int i = rank*n + 1; i < (rank + 1)*n + 1; i++){
		pi_estimate_part += one_term_of_sum(i, N);
	}
	std::cout << (4./N)*pi_estimate_part << std::endl;

	if (rank != 0){
		MPI_Ssend(&pi_estimate_part, 1, MPI_DOUBLE, 0, 0, comm);
	}

	if (rank == 0){
		for (int j = 1; j < size ; j++){
			MPI_Status status;
			double letter;
			MPI_Recv(&letter, 1, MPI_DOUBLE, j, 0, comm, &status);
			pi_estimate_part += letter;
		}
		pi_estimate_part = pi_estimate_part*(4./N);
		cout.precision(20);
		std::cout << pi_estimate_part << std::endl;
	}

	MPI_Finalize();
	return 0;
}