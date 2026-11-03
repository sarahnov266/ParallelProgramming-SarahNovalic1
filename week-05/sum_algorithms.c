#include <stdlib.h>
#include <math.h>
#include "sum_algorithms.h"

/*
 * 1. Standard double precision summation
 */
double do_sum(double* restrict var, long ncells)
{
    double sum = 0.0;

    for (long i = 0; i < ncells; i++) {
        sum += var[i];
    }

    return sum;
}

/*
 * 2. Long double summation
 */
long double do_ldsum(double* restrict var, long ncells)
{
    long double sum = 0.0L;

    for (long i = 0; i < ncells; i++) {
        sum += (long double)var[i];
    }

    return sum;
}

/*
 * 3. Pairwise summation
 */
double do_pair_sum(double* restrict var, long ncells)
{
    if (ncells <= 0) {
        return 0.0;
    }

    double *pwsum = malloc((size_t)ncells * sizeof(double));

    if (pwsum == NULL) {
        return NAN;
    }

    for (long i = 0; i < ncells; i++) {
        pwsum[i] = var[i];
    }

    long nmax = ncells;

    while (nmax > 1) {
        long pairs = nmax / 2;

        for (long i = 0; i < pairs; i++) {
            pwsum[i] = pwsum[2 * i] + pwsum[2 * i + 1];
        }

        if (nmax % 2 != 0) {
            pwsum[pairs] = pwsum[nmax - 1];
            nmax = pairs + 1;
        } else {
            nmax = pairs;
        }
    }

    double sum = pwsum[0];

    free(pwsum);

    return sum;
}

/*
 * 4. Kahan summation
 */
double do_kahan_sum(double* restrict var, long ncells)
{
    double sum = 0.0;
    double correction = 0.0;

    for (long i = 0; i < ncells; i++) {
        double y = var[i] - correction;
        double t = sum + y;

        correction = (t - sum) - y;
        sum = t;
    }

    return sum;
}

/*
 * 5. Knuth summation
 */
double do_knuth_sum(double* restrict var, long ncells)
{
    double sum = 0.0;
    double correction = 0.0;

    for (long i = 0; i < ncells; i++) {
        double u = sum;
        double v = var[i] + correction;
        double upt = u + v;
        double up = upt - v;
        double vpp = upt - up;

        sum = upt;
        correction = (u - up) + (v - vpp);
    }

    return sum + correction;
}
