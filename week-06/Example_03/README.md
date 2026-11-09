# Lab 06 – SIMD Vectorization

## 1. Introduction

In this lab, I worked with the `timestep` example. The main goal was to test different SIMD optimizations and see how GCC handles vectorization.

I tested three versions of the code: Opt1, Opt2 and Opt3. I also tested Opt3 with additional compiler flags.

## 2. My computer and compiler

- Operating system: Ubuntu 24.04 (WSL2)
- CPU: AMD Ryzen 5 5625U
- CPU architecture: AMD Zen3
- Compiler: GCC 13.3.0
- LIKWID: 5.5.1
- Vector width: 256 bits (32 bytes)

My CPU supports AVX2. One 256-bit vector can hold four `double` values.

## 3. Code versions

### Opt1

In Opt1, I added the SIMD reduction:

```c
#pragma omp simd reduction(min:mymindt)
```

This is used to find the smallest `dt` value from all loop iterations.

### Opt2

Opt2 uses the same reduction, but also has private variables:

```c
#pragma omp simd private(wavespeed, xspeed, yspeed, dt) reduction(min:mymindt)
```

The temporary variables are private for each SIMD iteration.

### Opt3

Opt3 also uses SIMD reduction. The difference is that the temporary variables are declared inside the loop.

### Opt3 with extra flags

For the last version, I used Opt3 with two additional compiler flags:

```bash
-fno-trapping-math -fno-math-errno
```

These flags allow the compiler to perform more floating-point optimizations.

## 4. Compiler options

I used these compiler options:

```bash
-g -O3 -fstrict-aliasing -ftree-vectorize -fopenmp-simd \
-march=native -mtune=native -mprefer-vector-width=256
```

I also used these options to get information about vectorization:

```bash
-fopt-info-vec-optimized -fopt-info-vec-missed
```

The compiler reports are saved in separate files:

- `compile_opt1.txt`
- `compile_opt2.txt`
- `compile_opt3.txt`
- `compile_opt3_fast.txt`

## 5. Compiler results

GCC reported that the main loop in all three versions was vectorized using 32-byte vectors.

| Version | Compiler result |
|---|---|
| Opt1 | Main loop vectorized using 32-byte vectors |
| Opt2 | Main loop vectorized using 32-byte vectors |
| Opt3 | Main loop vectorized using 32-byte vectors |
| Opt3 with extra flags | Main loop and an additional loop part vectorized |

For the first three versions, GCC also reported that another part of the loop could not be vectorized because of control flow.

For the final Opt3 version, I added:

```bash
-fno-trapping-math -fno-math-errno
```

After that, GCC also reported vectorization for an additional loop part.

The compiler reports show that the vector width is 32 bytes. This is 256 bits, which can hold four double values.

## 6. Program results

I compiled and ran all four versions. They all gave the same result:

```text
Minimum dt is 0.016964
```

| Version | Result |
|---|---:|
| Opt1 | 0.016964 |
| Opt2 | 0.016964 |
| Opt3 | 0.016964 |
| Opt3 with extra flags | 0.016964 |

This shows that all versions produced the same output for this test.

## 7. LIKWID results

At first, LIKWID could not access the hardware performance counters in WSL2. I used the following command to load the MSR module:

```bash
sudo modprobe msr
```

After this, the MSR device became available.

The `MEM_DP` performance group was not available in my LIKWID installation for the Zen3 architecture. I checked the available groups and used `FLOPS_DP` instead.

I measured the four versions with:

```bash
sudo likwid-perfctr -C 0 -f -g FLOPS_DP ./stream_triad_opt1
```

I used the same command for the other three executables.

The results were:

| Version | Runtime (s) | DP (MFLOP/s) | CPI |
|---|---:|---:|---:|
| Opt1 | 1.9397 | 41.2444 | 1.4869 |
| Opt2 | 1.6679 | 47.9645 | 1.4647 |
| Opt3 | 2.2419 | 35.6846 | 1.5669 |
| Opt3 with extra flags | 2.5106 | 31.8652 | 2.9046 |

The LIKWID output showed the following warning:

```text
Unknown fixed event 0x1
```

However, LIKWID still displayed other counters and performance metrics. I used Runtime (RDTSC), DP (MFLOP/s) and CPI for the comparison. Some other metrics, such as Runtime unhalted and Clock, were displayed as zero, so I did not use them.

### Explanation of the results

Opt2 had the best result in my measurements. It had the shortest runtime (1.6679 seconds), the highest DP performance (47.9645 MFLOP/s) and the lowest CPI (1.4647).

Opt3 with extra flags was slower in this measurement than the other versions. This shows that additional compiler optimizations do not always improve the execution time.

These are individual measurements, so the results can change depending on CPU load and system conditions.

The LIKWID reports are saved in:

- `likwid_opt1.txt`
- `likwid_opt2.txt`
- `likwid_opt3.txt`
- `likwid_opt3_fast.txt`

## 8. Conclusion

In this lab, I tested different SIMD versions of the `timestep` code.

All four versions produced the same result. GCC reported vectorization using 32-byte vectors, which means that four double values can fit in one vector.

The additional compiler flags helped GCC vectorize another part of the Opt3 code. However, this did not give a better runtime in my measurements.

According to my LIKWID results, Opt2 was the fastest version in this test.

I also managed to run LIKWID in WSL2 after loading the MSR module. I used the `FLOPS_DP` group because `MEM_DP` was not available for my CPU architecture in the installed LIKWID version.
