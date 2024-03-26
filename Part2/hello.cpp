#include <mpi.h>
#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int provided;
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED,&provided); // Specify the desired thread support level

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    #pragma omp parallel // OpenMP parallel region
    {
        int tid = omp_get_thread_num(); // Get the thread ID
        int num_threads = omp_get_num_threads(); // Get the total number of threads

        // Each thread prints its own message
        std::cout << "Hello from MPI rank " << rank << ", thread " << tid << " of " << num_threads << std::endl;
    }

    MPI_Finalize();
    return 0;
}
