# ParallelProgramming-SarahNovalic1
## Assignment 2 – Makefile and Valgrind
I created a Makefile to make compiling and running my C program easier. I added the `all`, `run`, `valgrind` and `clean` commands. I used compiler flags to enable warnings and debugging information. After compiling the program, I ran it with Valgrind to check for memory leaks and memory errors. The program displayed the first ten results and reported that all allocated memory was freed, with 0 errors detected.
 Valgrind Output
```text
First 10 results:
result[0] = 0.00
result[1] = 4.00
result[2] = 8.00
result[3] = 12.00
result[4] = 16.00
result[5] = 20.00
result[6] = 24.00
result[7] = 28.00
result[8] = 32.00
result[9] = 36.00
Memory allocated: 24000 bytes
HEAP SUMMARY:
in use at exit: 0 bytes in 0 blocks
total heap usage: 4 allocs, 4 frees, 25,024 bytes allocated
All heap blocks were freed -- no leaks are possible

ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```
Finally, I initialized a local Git repository and connected it to my existing GitHub repository to prepare the assignment for submission.
