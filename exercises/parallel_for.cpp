/*Isn't this task too light to notice an acutal speedup in the program?
Don't we pay too much for the overhead of using multiple threads?*/
#include <iostream>
#include <omp.h>
#include <chrono>
#define SIZE 1000000
using namespace std;

int a[SIZE];
int threads, size, s, iterations;

int function() {
    int i = 0;
    int total = 0;

    omp_set_num_threads(threads);

    #pragma omp parallel for reduction (+:total)
    for (i = 0; i < size; i++) {
        //#pragma omp critical
        total += a[i];
    }
    return total;
}

int main() {
    
  
    cout << "How many threads? " << endl;
    cin >> threads;

    cout << "Insert size of array: ";
    cin >> size;

    cout << "Insert how many times you want to repeat the execution: " << endl;
    cin >> iterations;

    for (int i = 0; i < size; i++){
        a[i] = i+1;
    }

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    int x = 0;

    while (x < iterations) {
        s = function();
        x++;
    }

    cout << "Result is: " << s << endl;

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl;       
    cout << "Time difference = " << chrono::duration_cast<chrono::seconds> (end - begin).count() << "[s]" << endl;        
    return 0;
}