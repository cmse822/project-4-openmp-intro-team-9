## Part 1: OpenMP Matrix-Matrix Multiplication

Question 1 and 2:
* Wall time for the OpenMP version: 0.0160184 s
* Wall time for the non-OpenMP version: 0.0159778 s 

Since both versions were executed with only one thread, and assuming they perform the same workload, the slight difference in wall times could be attributed to factors openMP setting up time, That is the reason why OpenMP version have slightly larger wall time.

Question 3 to 5:



## Part 2: Adding OpenMP threading to a simple MPI application

```
Hello from MPI rank 0, thread 0 of 4
Hello from MPI rank 0, thread 3 of 4
Hello from MPI rank 0, thread 2 of 4
Hello from MPI rank 0, thread 1 of 4
Hello from MPI rank 1, thread 0 of 4
Hello from MPI rank 1, thread 3 of 4
Hello from MPI rank 1, thread 2 of 4
Hello from MPI rank 1, thread 1 of 4
```
The output indicates a successful execution of a parallel MPI + OpenMP program with 2 MPI ranks and 4 OpenMP threads per rank.

## Part 3: Hybrid Parallel Matrix Multiplication
