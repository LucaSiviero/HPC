#include <iostream>
#include <chrono>
#include <omp.h>
#define SIZE 100000

using namespace std;

int a[SIZE];
int threads = 1;
int last_pos, size, iterations = 0;

int calculate(int partition) {
    int result = 0;
  
    #pragma omp for
    for (int i = last_pos; i < last_pos + partition; i++) {
        //cout << "accessing element " << a[i] << endl;
        #pragma omp critical
        result += a[i];   
    }

    last_pos += partition;
    cout << "partial result = " << result << endl;

    return result;
}

int main() {

    cout << "How many threads do you want to use?" << endl;

    cin >> threads;

    cout << "Please specify array size" << endl;
    cin >> size;

    cout << "Please specify how many times you want to repeat the calculation" << endl;
    cin >> iterations;

    for (int i = 0; i < size; i++) {
        a[i] = i+1;
    }

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();

    int i, s = 0;

    omp_set_num_threads(threads);

    int partial_results[threads];

    for(int x = 0; x < threads; x++) {
        partial_results[x] = 0;
    }

    int partition = size / threads;
    int remainder = size % threads;
    int last_pos = 0;

    //#pragma omp parallel shared(a), private(partial_results)
    //#pragma omp parallel for            
    //#pragma omp master
    {
        int x = 0;
        while(x < iterations) {
            for(int i = 0; i < threads; i++) {

                if(i == threads - 1) {
                    partial_results[i] = calculate(partition + remainder);
                }
                else {
                    partial_results[i] = calculate(partition);
                }
                
                cout << "From main, thread " << i << " calculated " << partial_results[i] << endl;
            }
            x++;   
        }
    }
    
    //#pragma omp barrier

    //#pragma omp single 
    for (int i = 0; i < threads; i++){
        cout << "partial result [" << i << "] = " << partial_results[i] << endl;
        s += partial_results[i];
    }  
    #pragma omp single 
    std::cout << "Value of total sum is: " << s << endl;
    #pragma omp barrier

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    std::cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::seconds> (end - begin).count() << "[s]" << endl;        

    return 0;
}


//1250025000        RESULT FOR 50000 SIZE