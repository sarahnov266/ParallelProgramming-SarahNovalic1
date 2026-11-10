# Lab 06 – Vectorization (Example_03)

## 1. Introduction

The goal of this assignment was to improve the `Example_03` code using different vectorization techniques. I used the optimization files from the official book repository: `timestep_opt1.c`, `timestep_opt2.c` and `timestep_opt3.c`.

I compiled and tested each version and checked the compiler output and performance results using LIKWID.

Vectorization means that the processor can perform the same operation on multiple data elements at the same time. This is called SIMD (Single Instruction, Multiple Data). It can improve program performance because one instruction works with several values instead of processing them one by one.

## 2. System and compiler

The tests were performed using:

- Operating system: Ubuntu 24.04.4 LTS (WSL2)
- Processor: AMD Ryzen 5 5625U with Radeon Graphics
- Architecture: AMD Zen 3
- Compiler: GCC 13.3.0
- LIKWID version: 5.5.1
- Vector width: 256 bits

I used the compiler option `-mprefer-vector-width=256`.

A 256-bit vector has a size of 32 bytes. Since one double value uses 64 bits (8 bytes), one vector can contain four double values.

This means that the processor can work with four double values in one vector instruction.

## 3. Compiler options

The following compiler options were used:

- `-O3` – enables a high level of compiler optimization.
- `-fstrict-aliasing` – allows the compiler to make assumptions about how pointers access memory.
- `-ftree-vectorize` – enables loop vectorization.
- `-fopenmp-simd` – enables OpenMP SIMD directives.
- `-march=native` – allows the compiler to use instructions supported by the current processor.
- `-mtune=native` – optimizes the generated code for the current processor.
- `-mprefer-vector-width=256` – tells the compiler to prefer 256-bit vector instructions.
- `-fopt-info-vec-optimized` and `-fopt-info-vec-missed` – show which loops were vectorized and which were not.

## 4. Optimization 1 – timestep_opt1.c

In the first version, I used the OpenMP SIMD directive with a reduction:

`#pragma omp simd reduction(min:mymindt)`

The reduction is needed because the program calculates the minimum timestep value. Each vector lane can calculate its own minimum value, and at the end these values are combined to get the final minimum.

The compiler reported:

`loop vectorized using 32 byte vectors`

This means that the main loop was vectorized using 256-bit vectors. However, another part of the loop was not vectorized because of control flow.

The program output was:

`Minimum dt is 0.016964`

## 5. Optimization 2 – timestep_opt2.c

In the second version, I used both `private` and `reduction` in the OpenMP SIMD directive:

`#pragma omp simd private(wavespeed, xspeed, yspeed, dt) reduction(min:mymindt)`

The `private` clause gives each SIMD lane its own copy of the temporary variables. This prevents different iterations from using the same temporary values.

The `reduction` clause combines the minimum values at the end of the loop.

The compiler also reported:

`loop vectorized using 32 byte vectors`

The main loop was vectorized using 256-bit vectors, while another part was not vectorized because of control flow.

The output was the same:

`Minimum dt is 0.016964`

## 6. Optimization 3 – timestep_opt3.c

In the third version, the temporary variables were declared inside the loop. This changes how the variables are handled during each iteration.

The SIMD directive with reduction was also used:

`#pragma omp simd reduction(min:mymindt)`

The compiler reported:

`loop vectorized using 32 byte vectors`

The main loop was vectorized using 256-bit vectors. Another part of the code was still not vectorized because of control flow.

The program produced the same result:

`Minimum dt is 0.016964`

## 7. Optimization 3 with additional compiler flags

As required in the assignment, I compiled `timestep_opt3.c` again using the additional flags:

- `-fno-trapping-math`
- `-fno-math-errno`

These options allow the compiler to make additional optimizations related to floating-point calculations. They also allow the compiler to make assumptions about floating-point exceptions and mathematical function error handling.

After adding these flags, the compiler reported that another loop part was also vectorized using 32-byte vectors.

This means that the compiler was able to vectorize more of the code than in the previous versions.

The program still produced:

`Minimum dt is 0.016964`

## 8. Vector width and comparison with the professor's example

The professor's example shows how LIKWID can be used to check whether the processor executes 128-bit or 256-bit packed double instructions.

A 128-bit vector contains two double values, while a 256-bit vector contains four double values.

In the professor's example, the following counters were used:

- `FP_ARITH_INST_RETIRED_128B_PACKED_DOUBLE`
- `FP_ARITH_INST_RETIRED_256B_PACKED_DOUBLE`
- `FP_ARITH_INST_RETIRED_SCALAR_DOUBLE`

These counters show the number of executed floating-point instructions of different widths.

In my case, I used an AMD Ryzen 5 5625U processor with Zen 3 architecture. The installed LIKWID version did not provide the `MEM_DP` performance group used in the professor's example.

I checked the available performance groups and used `FLOPS_DP` instead. This group provides information about double-precision floating-point performance.

Because the available group did not provide the same separate 128-bit and 256-bit counters as the professor's example, I used the GCC vectorization report to identify the vector width.

The compiler confirmed the use of 32-byte vectors, which means 256-bit vectors.

Therefore, the compiler output was used to check the vector width, while LIKWID was used to compare performance.

## 9. LIKWID performance results

I used the `FLOPS_DP` performance group to measure the performance of each version.

| Version | Runtime (s) | CPI | DP (MFLOP/s) |
|---|---:|---:|---:|
| Opt1 | 1.9397 | 1.4869 | 41.2444 |
| Opt2 | 1.6679 | 1.4647 | 47.9645 |
| Opt3 | 2.2419 | 1.5669 | 35.6846 |
| Opt3 Fast | 2.5106 | 2.9046 | 31.8652 |

Runtime shows how long the program needed to execute. Lower runtime means faster execution.

CPI (Cycles Per Instruction) shows the average number of processor cycles needed for one instruction. A lower CPI is generally better.

DP (MFLOP/s) shows double-precision floating-point performance. A higher value means more floating-point operations were performed per second.

Based on these measurements, Opt2 had the shortest runtime and the highest DP performance. It was the best result in this test.

The Opt3 version with additional flags was not faster in this measurement. This shows that additional compiler optimizations do not always make a program faster.

The measurements were performed in WSL2, so system activity and measurement conditions can also affect the results.

### LIKWID note

During the tests, LIKWID displayed the warning:

`Unknown fixed event 0x1`

However, it still displayed the other counters and performance results.

The values for `Runtime unhalted` and `Clock` were zero in these measurements, so they were not used for comparison. I used the RDTSC runtime, CPI and DP values instead.

## 10. Conclusion

In this assignment, I tested three different vectorization versions and one additional compilation of Opt3 with extra floating-point flags.

All versions produced the same minimum timestep result: `0.016964`.

The GCC compiler reported that the main loops were vectorized using 32-byte vectors. This means that 256-bit SIMD vectors were used, with four double values in each vector.

The first three versions still had some code that was not vectorized because of control flow. With the additional flags in Opt3, the compiler was able to vectorize another part of the code.

The LIKWID measurements showed that Opt2 had the best performance in my tests, with a runtime of 1.6679 seconds and 47.9645 MFLOP/s.

Overall, this assignment helped me understand how SIMD directives, reduction, private variables and compiler options can affect vectorization and program performance.
