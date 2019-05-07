#include <time.h>
#include <sys/time.h>
#include <unistd.h>
#include <iostream>
#include <stdlib.h>


double time_elapsed(struct timespec &, struct timespec &);
double *init_zeros_mat(int);
double *init_rand_mat(int, int);
double *init_zeros_vec(int);
double *init_rand_vec(int, int);

