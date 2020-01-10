# Pi_MPI

This repo contains a simple code to approximate the value of pi. There is a serial code and a code that runs in parallel, which uses the MPI library.

The serial code is compiled using your standard g++ compiler. For the parallel code, use "mpiCC -o pi main_pi.cpp" to compile, then e.g. "mpiexec -np 100" ./pi to run the code parallely on 100 processes.