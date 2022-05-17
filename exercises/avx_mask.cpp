#include <immintrin.h>
#include <iostream>
using  namespace std;


int main() {
    int array[8] = {0, 1, 2, 3};

    __m256i mask = {-1, 0, -1, 0};

    __m256i result = _mm256_maskload_epi32(array, mask);

    //load a registry of 8 floats
    __m256i array2 = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);

    //store the registry in memory
    _mm256_store_si256(&array2, result);
    //store the registry in memory
    _mm256_store_si256(&array2, result);

    int* f = (int*) &array2;

    for (int i = 0; i < 8; i++) {
        cout << f[i] << endl;
    }

    int* ints = (int*) &result;

    for (int i = 0; i < 8; i++) {
        std::cout << ints[i];
    }
    return 0;
}