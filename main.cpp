#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include <chrono>
#include <omp.h>
#include "insertion_sort.hpp"
#include "parallel_quicksort.hpp"
#include "sequential_quicksort.hpp"

void print_example(std::vector<double> &v) {
    std::cout << "Example" << std::endl;
    for (double& e: v) {
        std::cout << e << std::endl;
    }
    std::cout << std::endl;
}

int main() {

    int n;

    std::cout << "Size of example (leave blank for 10^6):" << std::endl;
    std::cin >> n;

    if (n == 0) {
        n = 1000000;
    }

    std::cout << n << std::endl;

    std::random_device r;
    std::default_random_engine gen(r());
    std::uniform_real_distribution<double> dist;

    std::vector<double> v(n);
    for (double& e: v) {
        e = dist(gen);
    }

    auto start = std::chrono::high_resolution_clock::now();

    parallel_quicksort(v.begin(), v.end(), std::less<>{}, 0);

    auto stop = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    const bool sorted = is_sorted(v.begin(), v.end(), std::less<>{});
    std::cout << "Elements are sorted: " << std::boolalpha << sorted << std::endl;
    std::cout << "Execution time sequential quicksort: " << duration.count() / 1000 << " ms (" << duration.count() << " microseconds)" << std::endl;

#pragma omp parallel sections
    {
#pragma omp section
        {
            printf ("id = %d, \n", omp_get_thread_num());
        }
#pragma omp section
        {
            printf ("id = %d, \n", omp_get_thread_num());
        }
    }

    return 0;
}
