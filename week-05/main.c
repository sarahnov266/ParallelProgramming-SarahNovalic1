#define _POSIX_C_SOURCE 199309L

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include "sum_algorithms.h"

#define ORDERS_OF_MAGNITUDE 1.0e9

void cpu_timer_start(struct timespec *tstart_cpu)
{
    clock_gettime(CLOCK_MONOTONIC, tstart_cpu);
}

double cpu_timer_stop(struct timespec tstart_cpu)
{
    struct timespec tstop_cpu;

    clock_gettime(CLOCK_MONOTONIC, &tstop_cpu);

    double seconds = (double)(tstop_cpu.tv_sec - tstart_cpu.tv_sec);
    double nanoseconds = (double)(tstop_cpu.tv_nsec - tstart_cpu.tv_nsec);

    return seconds + nanoseconds * 1.0e-9;
}

void print_result(const char *method, long double accurate_sum,
                  long double test_sum, double runtime)
{
    long double error = fabsl(test_sum - accurate_sum);
    long double relative_error = error / fabsl(accurate_sum);

    printf("%-18s | Error: %.12Le | Relative error: %.12Le | Runtime: %.8f s\n",
           method, error, relative_error, runtime);
}

int main(void)
{
    printf("============================================================\n");
    printf("       PARALLEL SUMMATION ALGORITHMS - TESTING\n");
    printf("============================================================\n");

    for (int pow_of_two = 10; pow_of_two <= 24; pow_of_two++) {

        long ncells = 1L << pow_of_two;
        long ncellsdiv2 = ncells / 2;

        printf("\n============================================================\n");
        printf("TESTING WITH 2^%d = %ld ELEMENTS\n", pow_of_two, ncells);
        printf("============================================================\n");

        double high_value = 1.0e-1;
        double low_value = 1.0e-1 / ORDERS_OF_MAGNITUDE;

        long double accurate_sum =
            (long double)ncellsdiv2 * (long double)high_value +
            (long double)ncellsdiv2 * (long double)low_value;

        double *energy = malloc((size_t)ncells * sizeof(double));

        if (energy == NULL) {
            fprintf(stderr, "Error: Memory allocation failed!\n");
            return 1;
        }

        for (long i = 0; i < ncells; i++) {
            energy[i] = (i < ncellsdiv2) ? high_value : low_value;
        }

        printf("Expected accurate sum: %.18Lg\n\n", accurate_sum);

        struct timespec timer;
        double runtime;
        double result;

        /* 1. Standard double */
        cpu_timer_start(&timer);
        result = do_sum(energy, ncells);
        runtime = cpu_timer_stop(timer);

        print_result("Standard double", accurate_sum,
                     (long double)result, runtime);

        /* 2. Long double */
        cpu_timer_start(&timer);
        long double ld_result = do_ldsum(energy, ncells);
        runtime = cpu_timer_stop(timer);

        print_result("Long double", accurate_sum, ld_result, runtime);

        /* 3. Pairwise */
        cpu_timer_start(&timer);
        result = do_pair_sum(energy, ncells);
        runtime = cpu_timer_stop(timer);

        print_result("Pairwise", accurate_sum,
                     (long double)result, runtime);

        /* 4. Kahan */
        cpu_timer_start(&timer);
        result = do_kahan_sum(energy, ncells);
        runtime = cpu_timer_stop(timer);

        print_result("Kahan", accurate_sum,
                     (long double)result, runtime);

        /* 5. Knuth */
        cpu_timer_start(&timer);
        result = do_knuth_sum(energy, ncells);
        runtime = cpu_timer_stop(timer);

        print_result("Knuth", accurate_sum,
                     (long double)result, runtime);

        free(energy);
    }

    printf("\n============================================================\n");
    printf("ALL TESTS COMPLETE!\n");
    printf("============================================================\n");

    return 0;
}
