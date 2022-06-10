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

    template <typename T, typename F, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    void copy_if(std::vector<T> &v_input, std::size_t const in_begin, std::size_t const in_end, std::vector<T> &v_output,
        std::size_t const out_begin, F functor) noexcept{
            queue myQueue;
            {
                buffer<T, 1> sourceBuf { v_input.data(), range<1> { v_input.size() } };
                buffer<T, 1> destBuf { v_output.data(), range<1> { v_output.size() } };
                myQueue.submit([&](handler &cgh){
                    accessor source { sourceBuf, cgh, read_only, no_init };
                    accessor dest { destBuf, cgh, write_only, no_init };
                    int i = 0;
                    cgh.parallel_for(range<1> (in_end - in_begin), [&](id<1> idx) {
                        if (functor) {
                            dest[i] = source[idx];
                            i++;
                        }
                    });
                });

            }
        }
        

};

int main() {
    
    /*std::vector<double> data(1024);
    exa::fill(data, 0, 1024, 1.250);
    std::vector<double> data2(10000);
    exa::sequence(data2, 0, 10000);
    for (int i = 0; i < data.size(); i++)
        std::cout << "data[" << i << "] = " << data[i] << std::endl;

    for (int i = 0; i < data2.size(); i++)
        std::cout << "data2[" << i << "] = " << data2[i] << std::endl;
    */

   std::vector<double> data(100);
   exa::sequence(data, 0, 100);
   std::vector<double> toCopy(100);
   exa::fill(toCopy, 0, 100, -1);
   exa::copy_if(data, 0, 100, toCopy, 0, [=] (auto const &i) -> bool {
        return data[i] >= 50;
   });

   for (int i = 0; i < toCopy.size(); i++){
       std::cout << toCopy[i] << std::endl;
   }
    
    return 0;
}