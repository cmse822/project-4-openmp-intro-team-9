#include <mpi.h>
#include <omp.h>
#include <iostream>

int main(int argc, char *argv[]) {
    int provided;
    // Initialize MPI with thread support
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    if (provided < MPI_THREAD_FUNNELED) {
        std::cerr << "The MPI implementation does not support the required thread level." << std::endl;
        MPI_Abort(MPI_COMM_WORLD, 1); // Abort if the desired thread support level is not provided
    }

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Get the rank of the process
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Get the total number of processes

    // Synchronize all processes before starting the parallel region
    MPI_Barrier(MPI_COMM_WORLD);

    #pragma omp parallel // OpenMP parallel region
    {
        int tid = omp_get_thread_num(); // Get the thread ID
        int num_threads = omp_get_num_threads(); // Get the total number of threads

        #pragma omp critical // Here critical section to manage orderly output
        {
            std::cout << "Hello from MPI rank " << rank << ", thread " << tid << " of " << num_threads << std::endl;
        }
    }

    // Finalize the MPI environment
    if (MPI_Finalize() != MPI_SUCCESS) {
        std::cerr << "Error finalizing MPI." << std::endl;
        return 1;
    }

    return 0;
}
