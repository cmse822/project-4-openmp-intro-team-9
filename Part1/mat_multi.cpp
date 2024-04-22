#include <iostream>
#include <fstream>  
#include <vector>
#include <random>
#include "get_walltime.c"

using namespace std;

// Function to perform matrix multiplication
vector<vector<float>> matrixMultiply(const vector<vector<float>>& A, const vector<vector<float>>& B) {
    int rows_A = A.size();
    int cols_A = A[0].size();
    int cols_B = B[0].size();

    vector<vector<float>> C(rows_A, vector<float>(cols_B, 0.0));

    for (int i = 0; i < rows_A; ++i) {
        for (int j = 0; j < cols_B; ++j) {
            for (int k = 0; k < cols_A; ++k) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    return C;
}

// Function to initialize a matrix with random values between 1 and 10
vector<vector<float>> initializeRandomMatrix(int rows, int cols) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> dis(1.0, 9.0);

    vector<vector<float>> matrix(rows, vector<float>(cols, 0.0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            matrix[i][j] = dis(gen);
        }
    }

    return matrix;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <matrix_size_N>" << endl;
        return 1;
    }

    const int N = atoi(argv[1]); // Matrix size
    const int num_iterations = 20; // Number of iterations

    // Initialize matrices A and B with random values between 1 and 10
    vector<vector<float>> A = initializeRandomMatrix(N, N);
    vector<vector<float>> B = initializeRandomMatrix(N, N);

    double total_elapsed_time = 0;

    for (int iteration = 0; iteration < num_iterations; ++iteration) {
        double start_time;
        get_walltime(&start_time);

        vector<vector<float>> result = matrixMultiply(A, B);

        double end_time;
        get_walltime(&end_time);

        total_elapsed_time += (end_time - start_time);
    }

    double average_elapsed_time = total_elapsed_time / num_iterations;

    // Calculate performance in Gflop/s
    double total_ops = 2.0 * N * N * N; // Total ops for all iterations
    double gflops = (total_ops / average_elapsed_time) * 1e-9;


    // Output results to a CSV file with header
    ofstream outFile("results_part1_q5_without_threads.csv", ios::app);  // Open file in append mode
    if (outFile.is_open()) {
        // Add header if the file is empty
        if (outFile.tellp() == 0) {
            outFile << "N,average_elapsed_time" << endl;
        }
        outFile << N << "," << average_elapsed_time << endl;
        outFile.close();
        cout << "Results appended to results.csv" << endl;
    } else {
        cerr << "Unable to open the output file." << endl;
        return 1;
    }


    return 0;
}
