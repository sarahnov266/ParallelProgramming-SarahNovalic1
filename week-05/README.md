# Assignment 5 – Summation Algorithms

## About

In this assignment, I tested five different methods for adding numbers in C. I wanted to compare their accuracy and runtime.

The methods are:
- Standard double
- Long double
- Pairwise
- Kahan
- Knuth

## How It Works

The program creates an array with big and small numbers. It tests different array sizes, from `2^10` to `2^24`.

For each size, all five methods are tested. The program shows the error and the time needed for each method.

## Results

The tests showed that Standard double was usually the fastest, but it had a bigger error.

Long double gave better results, while Pairwise, Kahan and Knuth had the smallest errors in my tests.

The results for the largest array (`2^24`) were:

| Method | Error | Runtime |
|---|---:|---:|
| Standard double | 1.4195e-05 | 0.0534 s |
| Long double | 5.3797e-08 | 0.1032 s |
| Pairwise | 4.7010e-11 | 0.2654 s |
| Kahan | 4.7010e-11 | 0.1753 s |
| Knuth | 4.7010e-11 | 0.2733 s |

All results for the tested array sizes are saved in `results.txt`.

## Connection to Parallel Programming

In parallel programming, different threads can calculate parts of a sum at the same time. Later, their results are combined.

However, adding numbers in a different order can give slightly different results because of rounding errors. This is why accurate summation is important.

## Conclusion

I learned that the fastest method is not always the most accurate. Pairwise, Kahan and Knuth gave the smallest errors in my tests, while Standard double was usually faster.

## How to Run

```bash
make
./sum_test
```

## Google Sheets Results

All results for the 15 tested array sizes and 5 summation methods are available in Google Sheets:

[Assignment 5 – Complete Summation Results](https://docs.google.com/spreadsheets/d/1aqnWqcyN04qAjVwNAHWFsSPB6PMQGPyocD-PppdhUo0/edit?gid=0#gid=0)
