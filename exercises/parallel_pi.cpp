#include <iostream>
#include <omp.h>
#include <chrono>

using namespace std;

int threads, iterations;

double calculatePi_with_partial_sums_padding(unsigned long int n);
double calculatePi_with_reduction(unsigned long int n);
double calculatePi_with_partial_sums_no_padding(unsigned long int n);
double calculatePi_with_critical_section(unsigned long int n);


double f(double x) {
    return (4.0 / (1.0 + x*x));     
}


int main() {

    cout << "How many threads? " << endl;
    cin >> threads;

    omp_set_num_threads(threads);
    cout << "Number of threads executing: " << omp_get_num_threads() << endl << endl;

    double result;

    cout << "Calculating the reduction manually without a padded array" << endl;

    chrono::steady_clock::time_point begin = chrono::steady_clock::now();
    result = calculatePi_with_partial_sums_no_padding(10000000);

    cout << "Result is :" << result << endl;

    chrono::steady_clock::time_point end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl << endl;       

    cout << "Now calculating the reduction manually storing the partial result in a padded array." << endl ;

    begin = chrono::steady_clock::now();
    result = calculatePi_with_partial_sums_padding(10000000);

    cout << "Result is :" << result << endl;

    end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl << endl;       

    cout << "Now calculating the reduction with the openMP directive." << endl;

    begin = chrono::steady_clock::now();
    result = calculatePi_with_reduction(10000000);

    cout << "Result is :" << result << endl;

    end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl << endl;       

    cout << "Now calculating the reduction with a critical section" << endl;

    begin = chrono::steady_clock::now();
    result = calculatePi_with_critical_section(10000000);

    cout << "Result is :" << result << endl;

    end = chrono::steady_clock::now();

    cout << "Time difference = " << chrono::duration_cast<chrono::microseconds>(end - begin).count() << "[µs]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::nanoseconds> (end - begin).count() << "[ns]" << endl;
    cout << "Time difference = " << chrono::duration_cast<chrono::milliseconds> (end - begin).count() << "[ms]" << endl << endl;       

    return 0;
}



double calculatePi_with_partial_sums_padding(unsigned long int n) {
    const double fH = 1.0 / (double) n;
    double fSum = 0.0;
    double fX;
    int i = 0;
    double partial_result[threads*8];
    #pragma omp parallel num_threads(threads)
    {   
        int t = omp_get_thread_num();
        #pragma omp for private(fX)
        for (i = 0; i < n; i++) {
            fX = fH * ((double)i + 0.5);
            partial_result[t*8] += f(fX);
        }
    }

    for (int i = 0; i < threads; i++) {
        fSum += partial_result[i*8];
    }
    
    return fH * fSum;
}


double calculatePi_with_reduction(unsigned long int n) {
    const double fH = 1.0 / (double) n;
    double fSum = 0.0;
    double fX;
    int i = 0;
    #pragma omp parallel num_threads(threads)
    {   
        #pragma omp for reduction(+:fSum) private(fX)
        for (i = 0; i < n; i++) {
            fX = fH * ((double)i + 0.5);
            fSum += f(fX);
        }
    }
    return fH * fSum;
}


double calculatePi_with_partial_sums_no_padding(unsigned long int n) {
    const double fH = 1.0 / (double) n;
    double fSum = 0.0;
    double fX;
    int i = 0;
    double partial_result[threads];
    #pragma omp parallel num_threads(threads)
    {   
        int t = omp_get_thread_num();
        #pragma omp for private(fX)
        for (i = 0; i < n; i++) {
            fX = fH * ((double)i + 0.5);
            partial_result[t] += f(fX);
        }
    }

    for (int i = 0; i < threads; i++) {
        fSum += partial_result[i];
    }
    return fH * fSum;
}

double calculatePi_with_critical_section(unsigned long int n) {
    const double fH = 1.0 / (double) n;
    double fSum = 0.0;
    double fX;
    int i = 0;
    #pragma omp parallel num_threads(threads)
    {
        #pragma omp for private(fX)
        for (i = 0; i < n; i++) {
            fX = fH * ((double)i + 0.5);
            #pragma omp critical
            fSum += f(fX);
        }
    }
    return fH * fSum;
}