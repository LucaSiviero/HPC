#include <oneapi/dpl/execution>
#include <oneapi/dpl/algorithm>
#include <CL/sycl.hpp>
#include <dpct/dpct.hpp>
#include <iostream>
#include <functional>
#include <numeric>
#include <vector>
#include <dpct/dpl_utils.hpp>
#ifndef _ONEDPL_BACKEND_SYCL
#define _ONEDPL_BACKEND_SYCL 1
#endif

template <typename T> using h_vec = std::vector<T>;
template <typename T1> using d_vector = dpct::device_vector<T1>;

template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
    void exclusive_scan(d_vector<T> const &v_input, std::size_t const in_begin, std::size_t const in_end, d_vector<T> &v_output, std::size_t const out_begin, T const init) noexcept {
            std::exclusive_scan(oneapi::dpl::execution::make_device_policy(
                                dpct::get_default_queue()),
                            v_input.begin() + in_begin,
                            v_input.begin() + in_end,
                            v_output.begin() + out_begin, init, 0);
    }

int main() {
    std::vector<int> d_v = {1 ,2, 3, 4, 5, 6, 7, 8, 9, 10};
    d_vector<int> d_vec  = d_v;
    std::cout << "Executing exclusive_scan on device" << std::endl;
    std::exclusive_scan( d_vec.begin(), d_vec.end(), std::ostream_iterator<int>(std::cout, " "), 0);
    
}