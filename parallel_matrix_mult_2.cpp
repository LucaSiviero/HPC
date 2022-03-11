#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>
#define SIZE 8192
using namespace std;

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], threads, matrix_size, iterations = 0;

void resetMatrix() {

    omp_set_num_threads(threads);
    #pragma omp parallel for
    for(int i = 0; i < matrix_size; i++){
        for(int j = 0; j < matrix_size; j++)
        {
            C[i][j]=0;
        }
    }
}

void parallel_mult() {

    omp_set_num_threads(threads);
    #pragma omp parallel for
    for (int k = 0; k < matrix_size; k++) {
        for (int j = 0; j < matrix_size; j++) {
            for(int i = 0; i < matrix_size; i++) {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }

    //Printing the matrix
    //#pragma omp parallel for
    /*for (int i = 0; i < matrix_size; i++) {
        for (int j = 0; j < matrix_size; j++) {
            cout << "|" << C[i][j] << "|"; 
        }
        cout << endl;
    }*/
    
}

int main() {

    int i, j, k, threads;
    cout << "How many threads?" << endl;
    cin >> threads;
    cout << "Enter rows and columns for the two matrices ( max 8192, only squared matrices ): ";
    cin >> matrix_size;
    cout << "Enter how many times the multiplication will be repeated: " << endl;
    cin >> iterations;
    
    // If column of first matrix in not equal to row of second matrix,
    // ask the user to enter the size of matrix again.
    while (threads <= 0) {
        cout << "Error! Threads must be at least 1.";
        
        cout << "How many threads?" << endl;
        cin >> threads;
        
        cout << "Enter rows and columns for the matrices: ";
        cin >> matrix_size;

    }

    int partition = matrix_size / threads;

    // Storing elements of first matrix.
    for(i = 0; i < matrix_size; ++i)
        for(j = 0; j < matrix_size; ++j)
        {
            A[i][j] = j+1;//i + 4 / 2;
        }

    // Storing elements of second matrix.
    for(i = 0; i < matrix_size; ++i)
        for(j = 0; j < matrix_size; ++j)
        {
            B[i][j] = j+1;
        }
/*      Showing matrices
        cout << "Matrix A is: " << endl;
        for(i = 0; i < matrix_size; ++i)
            for(j = 0; j < matrix_size; ++j)
            {
                cout << " " << A[i][j];
                if(j == matrix_size-1)
                    cout << endl;
            }
        cout << "Matrix B is: " << endl;

        for(i = 0; i < matrix_size; ++i)
            for(j = 0; j < matrix_size; ++j)
            {
                cout << " " << B[i][j];
                if(j == matrix_size-1)
                    cout << endl;
            }
*/
        // Initializing elements of matrix mult to 0.
    for(i = 0; i < matrix_size; ++i){
        for(j = 0; j < matrix_size; ++j)
        {
            C[i][j]=0;
        }
    }

    //#pragma omp parallel num_threads(threads) 
    
    


    int x = 0; 
    omp_set_num_threads(threads);

    #pragma omp single
    cout << "The number of threads executing is: " << omp_get_num_threads() << endl;
    
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    
    #pragma omp parallel num_threads(threads)
    {
        while (x < iterations) {
        parallel_mult();
        resetMatrix();
        x++;
        }
    }
    //Parallel computation...    
    //#pragma omp task
    

    //#pragma omp taskwait
    
    //Measuring end of time.
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl;       
    cout << "Time difference = " << chrono::duration_cast<chrono::seconds> (end - begin).count() << "[s]" << endl;        
 
    return 0;

}