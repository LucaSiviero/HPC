#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>
#define SIZE 8192
using namespace std;

int A[SIZE][SIZE], B[SIZE][SIZE], C[SIZE][SIZE], threads, matrix_size;
int last_index = 0;
int iterations = 0;


void parallel_mult(int partition) {
    last_index = 0;
    omp_set_num_threads(threads);

    #pragma omp parallel for
    for (int k = last_index; k < last_index + partition; k++) {
        for (int i = 0; i < matrix_size; i++) {
            for(int j = 0; j < matrix_size; j++) {
                C[i][j] += A[i][k] * B[k][j];
            }
            //Debugging instruction
            //cout << "The element in position " << i << "-" << j << " is: " << C[i][j] << endl;
        }
    }
    //Printing the matrix for each processor.
    /*
    #pragma omp parallel for
    for (int i = last_index; i < last_index + partition; i++) {
        for (int j = last_index; j < last_index + partition; j++) {
            cout << "|" << C[i][j] << "|"; 
        }
        cout << endl;
    }
    */

    last_index += partition;
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
    for(i = 0; i < matrix_size; ++i)
        for(j = 0; j < matrix_size; ++j)
        {
            C[i][j]=0;
        }


    #pragma omp parallel num_threads(threads)

    #pragma omp single
    cout << "The number of threads executing is: " << omp_get_num_threads() << endl;
    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    int x = 0; 

    while (x < iterations) {
        parallel_mult(partition);
        x++;
    }
    //Parallel computation...    
    //#pragma omp task
    

    //#pragma omp taskwait
    
    //Measuring end of time.

    
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();


    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl;       
    cout << "Time difference = " << chrono::duration_cast<chrono::seconds> (end - begin).count() << "[s]" << endl;        
 
    return 0;

}