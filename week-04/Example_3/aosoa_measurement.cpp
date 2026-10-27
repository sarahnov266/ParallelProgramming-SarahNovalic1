
//
// Created by Adnan Hajro on 17. 10. 2025..
//
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <chrono>

// V is defined by the Makefile via the -D flag, e.g., -DV=4
#ifndef V
#define V 4
#endif

struct SoA_type {
    int R[V], G[V], B[V];
};

void run_aos_aoa_kernel(long len) {
    long num_blocks = (len + V - 1) / V;

    // allocate array of SoA_type structures - IT'S C++
    SoA_type* AoSoA = new SoA_type[num_blocks];

    auto start = std::chrono::steady_clock::now();
    for (long j = 0; j < num_blocks; j++) {
        for (int i = 0; i < V; i++) {
            if ((j * V + i) < len) {
                AoSoA[j].R[i] = rand();
                AoSoA[j].G[i] = rand();
                AoSoA[j].B[i] = rand();
            }
        }
    }

    auto end = std::chrono::steady_clock::now();

    // deallocate the resources
    delete[] AoSoA;

    auto duration_ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start);

    double total_time_ms = duration_ns.count() / 1000000.0;
    std::cout << len << ", " << V << ", " << total_time_ms << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <N>" << std::endl;
        return 1;
    }

    long len = std::atol(argv[1]);

    if (len <= 0) {
        std::cerr << "N must be a positive integer." << std::endl;
        return 1;
    }

    run_aos_aoa_kernel(len);
    return 0;
}

