# Example 3 – AoSoA Benchmark

## About the Project

This experiment measures the execution time of the AoSoA program for different array sizes and vector lengths.

The program uses three arrays: `R`, `G`, and `B`, and measures the time needed to process their elements.

N – number of elements
V – vector length
Execution time – measured in milliseconds (ms)

## Test Configuration

The tests were performed using C++ and the `g++` compiler.

Vector lengths tested:

`V = 2, 4, 8, 16, 32, 64, 128, 256`

Array sizes tested:

`N = 1,000; 10,000; 100,000; 1,000,000; 10,000,000`

## Results Table

The following table shows the measured execution times for `N = 10,000,000`.

| N | Vector Length (V) | Execution Time (ms) |
|---:|---:|---:|
| 10,000,000 | 2 | 535.503 |
| 10,000,000 | 4 | 509.672 |
| 10,000,000 | 8 | 545.083 |
| 10,000,000 | 16 | 554.357 |
| 10,000,000 | 32 | 475.991 |
| 10,000,000 | 64 | 567.843 |
| 10,000,000 | 128 | 371.449 |
| 10,000,000 | 256 | 339.083 |

The full results for all tested array sizes are available in the CSV files in this folder.

## Graph

The graph compares the execution times for different vector lengths.

![AoSoA Benchmark Graph](graph.png)

## Google Sheets

[Open the complete results table and graph in Google Sheets](https://docs.google.com/spreadsheets/d/1Ctqc2t4ndNYEEA4FsVgJdkGCJ1KkSzHrk-CLpX8uFcM/edit?gid=0#gid=0)

## What I Learned

The execution time changes depending on the array size and vector length. A larger vector length does not always guarantee better performance. In my latest test with 10,000,000 elements, `V = 256` had the lowest execution time, approximately 339.083 ms.

## Conclusion

This experiment helped me understand how to measure program performance and compare different vector lengths using execution-time results and a graph.
