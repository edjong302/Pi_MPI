#include<math.h>
#include <iostream>
#include <mpi.h>
using namespace std;

double one_term_of_sum(int ii, int iN){ // Computes one term in series approximation for pi
	double term = 1/(1 + pow((ii - .5)/double(iN), 2.));
	return term;
}

int main(int argc, char** argv){
	MPI_Init(NULL, NULL);

	// Initial values
	int N = 8400;
	int size, rank;
	MPI_Comm comm;
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	comm = MPI_COMM_WORLD;

	// Number of terms of sum done by each processor
	int n = N/size;
	
	// Pi approximation: different part of sum done by every processor
	double pi_estimate_part = 0.;
	for (int i = rank*n + 1; i < (rank + 1)*n + 1; i++){
		pi_estimate_part += one_term_of_sum(i, N);
	}

	
	// Synchronously send outcome to rank 0
	if (rank != 0){
		MPI_Ssend(&pi_estimate_part, 1, MPI_DOUBLE, 0, 0, comm);
	}

	// Receive outcomes and add them up, then print
	if (rank == 0){
		for (int j = 1; j < size ; j++){
			MPI_Status status;
			double letter;
			MPI_Recv(&letter, 1, MPI_DOUBLE, j, 0, comm, &status);
			pi_estimate_part += letter;
		}
		pi_estimate_part = pi_estimate_part*(4./N);
		cout.precision(14);
		std::cout << "The MPI estimate for pi is" << " " << pi_estimate_part << "." << std::endl;
	}

	MPI_Finalize();
	return 0;
}