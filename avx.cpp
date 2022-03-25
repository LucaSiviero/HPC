/*
Implement an AVX program that:
1 - adds two array of floats;
2 - adds the only odd (or even) elements of two arrays of floats;
3 - computes the dot product;
4 - vectorizes a loop.

Remember that for all 4 exercises: input data must be dinamically allocated. Input size can be a multiple of 8. Compare result with a simple loop in -O0, with and without data alignment.
*/

#include <immintrin.h>
#include <iostream>

#define SIZE 10

using namespace std;

void simple_sum_sp();
void allocated_array_sum_sp();

int main() {

    //simple_sum_sp();
    
    allocated_array_sum_sp();

    return 0;
}


void simple_sum_sp() {

    //Remember: set inserts in memory all the elements in memory following this order: float7 - float6 - ... - float0.
    //To insert them as listed in the function call, we use setr.
    __m256 array1 = _mm256_setr_ps(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0);
    __m256 array2 = _mm256_setr_ps(2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0);

    __m256 result = _mm256_add_ps(array1, array2);

    float* f = (float*) &result;

    for(int i = 0; i < 8; i++) {
        cout << f[i] << endl;
    }
}


void allocated_array_sum_sp() {

    float* aligned_floats = (float*) aligned_alloc(32, SIZE * sizeof(float));
    float* aligned_floats2 = (float*) aligned_alloc(32, SIZE * sizeof(float));

    cout << "First array is: " << endl;
    for (int i = 0; i < SIZE; i++) {
        aligned_floats[i] = (float) i + 0.1;
        cout << aligned_floats[i] << endl;

    }

    __m256 vector = _mm256_load_ps(aligned_floats);

    cout << "Second array is: " << endl;

    for (int i = SIZE - 1; i >= 0; i--) {
        aligned_floats2[i] = (float) i + 0.1;
        cout << aligned_floats2[i] << endl;
    }
    __m256 vector2 = _mm256_load_ps(aligned_floats2);

    __m256 result = _mm256_add_ps(vector, vector2);

    float* f_result = (float*) &result;

    cout << "The result is:" << endl;

    for(int i = 0; i < SIZE; i++) {
        cout << f_result[i] << endl;
    }

}