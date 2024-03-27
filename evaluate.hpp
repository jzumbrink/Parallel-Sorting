#pragma once

#include <chrono>
#include <omp.h>
#include <iterator>

template<class It, class Comp>
void evaluate_sorting_algorithm(std::string name, void (*sort_func) (It, It, Comp), It begin, It end, Comp comp) {
    auto start = std::chrono::high_resolution_clock::now();

    sort_func(begin, end, comp);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    const bool sorted = is_sorted(begin, end, comp);
    std::cout << "===" << name << "===" << std::endl;
    std::cout << "Elements are sorted: " << std::boolalpha << sorted << std::endl;
    std::cout << "Execution time: " << duration.count() / 1000 << " ms (" << duration.count() << " microseconds)" << std::endl << std::endl;
}