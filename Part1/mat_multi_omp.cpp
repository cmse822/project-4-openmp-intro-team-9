#include <iostream>
#include <fstream>  
#include <vector>
#include <random>
#include <omp.h> // Include OpenMP header
#include "get_walltime.c"

using namespace std;

int main(int argc, char* argv[]) {
    int i,j,k;
    
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <matrix_size_N>" << endl;
        return 1;
    }
    
    const int N = atoi(argv[1]); // Matrix size
    const int num_iterations = 10; // Number of iterations

    // Initialize matrices A, B, and C with random values between 1 and 10
    vector<vector<float>> A(N, vector<float>(N));
    vector<vector<float>> B(N, vector<float>(N));
    vector<vector<float>> C(N, vector<float>(N)); // C will be a N*N matrix with 0 initialize

    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(1.0, 9.0);

    // Initialize matrices A and B with random values
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            A[i][j] = dis(gen);
            B[i][j] = dis(gen);
        }
    }

    double total_elapsed_time = 0;
    float sum = 0.0;
    int nthread = 0;

    for (int iteration = 0; iteration < num_iterations; ++iteration) {
        double start_time;
        get_walltime(&start_time);

        #pragma omp parallel private(i,j,k) shared(A,B,C) // OpenMP parallel region
        {
            // Get the actual number of threads within the parallel region
            int id, nthrd;
            id  = omp_get_thread_num();
            nthrd = omp_get_num_threads();
            if (id==0) nthread = nthrd;
            
            #pragma omp for
            for (i = 0; i < N; ++i) {
                for (j = 0; j < N; ++j) {
                    #pragma omp simd reduction(+:sum)
                    for (k = 0; k < N; ++k) {
                        sum += A[i][k] * B[k][j];
                    }
                    C[i][j] = sum;
                }   
            }
        }

        double end_time;
        get_walltime(&end_time);

        total_elapsed_time += (end_time - start_time);
    }

    double average_elapsed_time = total_elapsed_time / num_iterations;
    
    // Output results to a CSV file with header
    ofstream outFile("results.csv", ios::app);  // Open file in append mode
    if (outFile.is_open()) {
        // Add header if the file is empty
        if (outFile.tellp() == 0) {
            outFile << "N,nthread,average_elapsed_time" << endl;
        }
        outFile << N << ","<< nthread << "," << average_elapsed_time << endl;
        outFile.close();
        cout << "Results appended to results.csv" << endl;
    } else {
        cerr << "Unable to open the output file." << endl;
        return 1;
    }

    return 0;
}
