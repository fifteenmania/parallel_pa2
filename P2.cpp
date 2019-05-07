#include <iostream>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>
#include <algorithm>
#include "utils.hpp"
#define SIM_THRES 0.001

using namespace std;

// random matries
double *A, *A0 = NULL;
// results
double *b, *b0 = NULL;
// consts
int n = 0, p = 0;

/*
inline int get_pivot(int col)
{
    int pivot_row = col;
    double pivot_max = abs(A[col*n+col]);
    for (int i=col+1; i<n; i++){
        if (fabs(A[i*n+col])>pivot_max){
            pivot_max = abs(A[i*n+col]);
            pivot_row = i;
        }
    }
    return pivot_row;
}*/
inline void swap_vec(int i, int j)
{
    double temp = b[i];
    b[i] = b[j];
    b[j] = temp;
}

void GE_single()
{
    for (int i=0; i<n-1; i++){
        int piv = distance(A, max_element(A+i*n, A+i*n+n));
        swap_ranges(A+i*n, A+i*n+n, A+piv*n);
        swap_vec(i, piv);
        for (int j=i+1; j<n; j++){
            int a = A[j*n+i]/A[piv*n+piv];
            for (int k=i; k<n; k++){
                A[j*n+k] -= a*A[i*n+j];
            }
            b[j] -= a*b[i];
        }
    }
    return;
}

void GE_omp()
{
    return;
}

void backsub()
{
    return;
}

double l2_norm()
{

    return 0;
}

int main(int argc, char **argv)
{
    if (argc !=3){
        cout << "usage: [n]:size of input [p]:number of threads" << endl;
        return 0;
    }
    n = atoi(argv[1]);
    p = atoi(argv[2]);

    A = init_rand_mat(n, 2);
    b = init_rand_vec(n, 2);
   
    print_mat(A, n);
    struct timespec begin, end;
    // multi thread
    clock_gettime(CLOCK_MONOTONIC, &begin);
    GE_single();
    clock_gettime(CLOCK_MONOTONIC, &end);
    cout << "Parallel: " << time_elapsed(begin, end) << " ms" << endl;
    
    print_mat(A, n);
    // correctness
    double resid = l2_norm();
    cout << "Residual: " << resid << endl;
    cout << "Correcct: " << (resid<SIM_THRES) << endl;

    return 0;
}

