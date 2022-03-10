/*
Parallel dot product program. We start with two vectors, A and B. The result is an integer. a*b = for(i in a, b): total += a[i] * b[i]
*/
#include <iostream>
#include <chrono>
#include <thread>
#include <omp.h>
#define SIZE 500000
using namespace std;

int A[SIZE], B[SIZE], threads, size, iterations;

int dot_product() {
    unsigned long int total = 0;
    omp_set_num_threads(threads);

    #pragma omp parallel for reduction(+: total)
    for (int i = 0; i < size; i++) {
        //#pragma omp critical
        total += A[i] * B[i];
    }
    return total;
}

int main() {

    cout << "How many threads? " << endl;
    cin >> threads;

    cout << "Insert size of array: " << endl;
    cin >> size;

    cout << "Insert how many times you want to repeat the execution: " << endl;
    cin >> iterations;
 

    for (int i = 0; i < size; i++) {
        A[i] = i+1;
        B[i] = i+1;
    }

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    unsigned long int result = 0;
    int x = 0; 

    while(x < iterations) {
        result = dot_product();
        x++;
    }
    cout << result << endl;
    
    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl;       
    cout << "Time difference = " << chrono::duration_cast<chrono::seconds> (end - begin).count() << "[s]" << endl;   
    return 0;
}