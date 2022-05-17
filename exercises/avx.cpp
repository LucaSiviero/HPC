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
#include <stdio.h>

#define SIZE 1024

using namespace std;

void simple_sum_sp();
void allocated_array_sum_sp();
void function();

int main() {

    //simple_sum_sp();
    allocated_array_sum_sp();

    return 0;
}


void simple_sum_sp() {

    //Remember: set inserts in memory all the elements in memory following this order: float7 - float6 - ... - float0.
    //To insert them as listed in the function call, we use setr.
    __m256 array1 = _mm256_setr_ps(0.1, 1.1, 2.1, 3.1, 4.1, 5.1, 6.1, 7.1);
    __m256 array2 = _mm256_setr_ps(2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0);

    __m256 result = _mm256_add_ps(array1, array2);

    float* f = (float*) &result;

    for(int i = 0; i < 8; i++) {
        cout << f[i] << endl;
    }
}

/*
void allocated_array_sum_sp() {

    float* aligned_floats = (float*) aligned_alloc(32, SIZE * sizeof(float));
    float* aligned_floats2 = (float*) aligned_alloc(32, SIZE * sizeof(float));

    cout << "First array is: " << endl;
    for (int i = 0; i < SIZE; i++) {
        aligned_floats[i] = (float) i + 0.1;
        cout << aligned_floats[i] << endl;
    }

    //Since every float is 4 bytes (32 bits), I multiply the number of elements for the amount of bit needed for each element.
    //I get the bit size to store the elements. Total bit size / register size is equal to number of registers needed.
    int registers_needed = (SIZE * 32) / 256;

    __m256 array[registers_needed];
    int offset = 0;

    for(int i = 0; i < registers_needed; i++) {
        for(int j = offset; j < offset + 8; j++) {
            array[i] = _mm256_load_ps();
        }
    }

   //__m256 vector = _mm256_load_ps(aligned_floats);

    cout << "Second array is: " << endl;

    for (int i = SIZE - 1; i >= 0; i--) {
        aligned_floats2[i] = (float) i + 0.1;
        cout << aligned_floats2[i] << endl;
    }
    __m256 vector2 = _mm256_load_ps(aligned_floats2);

    __m256 result = _mm256_add_ps(vector2, vector);

    float* f_result = (float*) &result;

    cout << "The result is:" << endl;

    for(int i = 0; i < SIZE; i++) {
        cout << f_result[i] << endl;
    }

}
*/

void allocated_array_sum_sp() {

    int registers_needed = (SIZE * 32) / 256;
    //If i have to store 1024 elements in different arrays of size 8, I need SIZE / 8 arrays.
    int num_rows = SIZE / 8;
    cout << "To store " << SIZE << " elements you need " << num_rows << " rows with 8 elements each" << endl;
    float** array_of_floats = (float**) aligned_alloc(num_rows * 32, sizeof(float*));

    for(int i = 0; i < num_rows; i++) {
        array_of_floats[i] = (float*) aligned_alloc(32*8, 8 * sizeof(float));
        //cout << "Wee " << i << endl;
    }

    int offset = 0;
    for(int i = 0; i < num_rows; i++) {
        for(int j = 0; j < 8; j++) {
            array_of_floats[i][j] = (float) (j + offset + 0.1);
            //cout << array_of_floats[i][j] << endl;
        }
        offset += 8;

    }
    
/*
    for(int i = 0; i < num_rows; i++) {
        for(int j = 0; j < 8; j++) {
            cout << "element " << i << " - " << j << "is: ";
            cout << array_of_floats[i][j] << endl;
        }
    }
*/

    __m256 array_of_vectors[num_rows];

    __m256 array_of_vectors2[num_rows];

    __m256 result[num_rows];

    for(int i = 0; i < num_rows; i++) {
        array_of_vectors[i] = _mm256_load_ps(array_of_floats[i]);
        array_of_vectors2[i] = _mm256_load_ps(array_of_floats[i]);
    }
    
    
    for (int i = 0; i < num_rows; i++) {
        result[i] = _mm256_add_ps(array_of_vectors[i], array_of_vectors2[i]);
    }
    
    for(int i = 0; i < num_rows; i++) {
        for (int j = 0; j < 8; j++) {
            cout << (float) result[i][j] << endl;
        }
    }
}