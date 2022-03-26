#include <immintrin.h>
#include <iostream>


#define SIZE 1024

using namespace std;

void allocated_array_sum_sp();


int main() {

    allocated_array_sum_sp();

    return 0;
}


void allocated_array_sum_sp() {

    int registers_needed = (SIZE * 32) / 256;
    //If i have to store 1024 elements in different arrays of size 8, I need SIZE / 8 arrays.
    int num_rows = SIZE / 8;
    cout << "To store " << SIZE << " elements you need " << num_rows << " rows with 8 elements each" << endl;
    float** array_of_floats = (float**) aligned_alloc(num_rows * 32, sizeof(float*));

    for(int i = 0; i < num_rows; i++) {
        array_of_floats[i] = (float*) aligned_alloc(32*8, 8 * sizeof(float));
    }

    int offset = 0;
    for(int i = 0; i < num_rows; i++) {
        for(int j = 0; j < 8; j++) {
            array_of_floats[i][j] = (float) (j + offset + 0.1);
        }
        offset += 8;

    }

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