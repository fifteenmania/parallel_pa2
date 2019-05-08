#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include "utils.hpp"

using namespace std;

// random matries
double *A, *B = NULL;
// results
double *C, *D = NULL;
// consts
int n = 0, p = 0;

void multiply_single()
{
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                C[i*n+k] += A[i*n+j]*B[n*j+k];
            }
        }
    }
}

void multiply_omp()
{
    #pragma omp parallel for num_threads(p)
    for (int i=0; i<n; i++){
        for (int j=0; j<n; j++){
            for (int k=0; k<n; k++){
                D[i*n+k] += A[i*n+j]*B[n*j+k];
            }
        }
    }
}

bool mat_equal()
{
    for (int i=0; i<n*n; i++){
        if (C[i] != D[i])
            return false;
    }
    return true;
}

int main(int argc, char **argv)
{
    if (argc !=3){
        cout << "usage: [n]:size of input [p]:number of threads" << endl;
        return 0;
    }
    n = atoi(argv[1]);
    p = atoi(argv[2]);

    A = init_rand_mat(n, 1);
    B = init_rand_mat(n, 2);
    C = (double *)init_zeros_mat(n);
    D = (double *)init_zeros_mat(n);
    
    struct timespec begin, end;
    // single thread
#ifndef BENCH
    clock_gettime(CLOCK_MONOTONIC, &begin);
    multiply_single();
    clock_gettime(CLOCK_MONOTONIC, &end);
    cout << "Single:   " << time_elapsed(begin, end) << " ms" << endl;
#endif

    // multi thread
    //
    clock_gettime(CLOCK_MONOTONIC, &begin);
    multiply_omp();
    clock_gettime(CLOCK_MONOTONIC, &end);
    cout << "Parallel: " << time_elapsed(begin, end) << " ms" << endl;

#ifndef BENCH
    // correctness
    cout << "Correct:  " << mat_equal() << endl;
#endif
    return 0;
}

