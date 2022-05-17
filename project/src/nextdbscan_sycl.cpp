#include <iostream>
#include <vector>
#include <CL/sycl.hpp>
using namespace cl::sycl; 

namespace exa {
    template <typename T>

    void fill(std::vector<T> &v, std::size_t const begin, std::size_t const end, T const val) noexcept {
        queue myQueue;
        {
            buffer<T, 1> resultBuf { v.data(), range<1> { v.size() } };
            myQueue.submit([&](handler& cgh) {
                accessor writeResult { resultBuf, cgh, write_only, no_init };
                cgh.parallel_for(range<1> (end - begin), [=](id<1> idx) {
                    writeResult[idx] = val;
                });
            });
        }
    }
    
    template <typename T>
    void sequence(std::vector<T> &v, std::size_t const begin, std::size_t const end) noexcept {
        queue myQueue;
        {
            buffer<T, 1> resultBuf { v.data(), range<1> { v.size() } };
            myQueue.submit([&](handler& cgh) {
                accessor writeResult { resultBuf, cgh, write_only, no_init };
                cgh.parallel_for(range<1> (end - begin), [=](id<1> idx) {
                    writeResult[idx] = idx;
                });
            });
        }
    }
};

int main() {
    
    std::vector<int> data(1024);
    exa::fill(data, 0, 1024, 1);
    for (int i = 0; i < 1024; i++)
        std::cout << "data[" << i << "] = " << data[i] << std::endl;
}