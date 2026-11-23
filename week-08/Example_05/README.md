# Lab 08 – MPI Collective Communication

## Introduction

In this lab, I worked with MPI collective communication functions. The main goal was to calculate the sum of all elements in an array using multiple processes.

The array has 10,000 elements. The main process (rank 0) creates the array and fills it with numbers from 1 to 10,000.

The final sum should be **50,005,000**.

## Code Implementation

### Dividing the Array

First, I divided the array between all available processes.

I used `base` and `remainder` to calculate how many elements each process should get. I also calculated the starting and ending indexes for each process.

### MPI_Allgather

I used `MPI_Allgather` to share the number of elements assigned to each process.

All processes receive this information and store it in the `nsizes` array.

I also calculated the `offsets` array, which tells MPI where each part of the global array starts.

### MPI_Scatterv

I used `MPI_Scatterv` to send parts of the global array from the main process to all other processes.

Each process receives its own part of the array and stores it in `a_local`.

### Calculating the Sum

After receiving the elements, each process calculates its own partial sum.

The result is stored in the variable `local_sum`.

### MPI_Reduce

I used `MPI_Reduce` to combine all partial sums into one final sum.

The operation `MPI_SUM` adds all the values together. The final result is received by the main process (rank 0).

### Memory Deallocation

Only rank 0 frees `a_global` because this array is allocated only by the main process.

Every process frees its own local array `a_local`.

## Testing and Results

I tested the program with 2, 4 and 8 processes.

### Test with 2 Processes

- Each process received 5,000 elements.
- Scatter time: 0.000803 seconds
- Reduce time: 0.000022 seconds
- Final sum: **50,005,000.00**

Screenshot: `screenshots/MPI_2_processes.png.png`

### Test with 4 Processes

- Each process received 2,500 elements.
- Scatter time: 0.000229 seconds
- Reduce time: 0.000266 seconds
- Final sum: **50,005,000.00**

Screenshot: `screenshots/MPI_4_processes.png.png`

### Test with 8 Processes

- Each process received 1,250 elements.
- Scatter time: 0.000709 seconds
- Reduce time: 0.000374 seconds
- Final sum: **50,005,000.00**

Screenshot: `screenshots/MPI_8_processes.png.png`

## Conclusion

All three tests worked successfully.

The final sum was the same in all tests: 50,005,000.00.

This lab helped me understand how MPI processes can share data, calculate smaller parts of a task and combine their results into one final result.
