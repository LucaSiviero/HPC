/*
Dato un array di 10000 numeri casuali nel range [1-100], implementa un algoritmo parallelo che conta quanti elementi cadono negli intervalli [0 - 10], [11 - 20], [21-30] e così via
*/

#include <iostream>
#include <chrono>
#include <omp.h>
#define SIZE 10000
using namespace std;

int container[10], threads;

int main() {

    int r = 0;

    for (int i = 0; i < 10; i++) {
        container[i] = 0;
    }

    cout << "How many threads?" << endl;

    cin >> threads;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for reduction(+:container)
        for(int i = 0; i < SIZE; i++) {
            srand(i + time(NULL));
            r = rand() % 100;
            r == 0 ? r+=1 : r;

            for(int j = 1; j < 100; j += 10) {
                if((r <= j + 9) && (r >= j)) {
                    //#pragma omp atomic
                    container[j/10]+= 1;
                }
            }
        }
    }

    int total = 0;

    for (int i = 0; i < 10; i++) {
        cout << "Section " << i << " contains " << container[i] << " elements" << endl;
        total += container[i];
    }
    cout << total << endl;

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl;       
    cout << "Time difference = " << chrono::duration_cast<chrono::seconds> (end - begin).count() << "[s]" << endl;        
    
    return 0;
}