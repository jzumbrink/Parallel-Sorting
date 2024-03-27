#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "insertion_sort.hpp"
#include "parallel_quicksort.hpp"
#include "sequential_quicksort.hpp"
#include "evaluate.hpp"

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

    std::vector<double> original_v(n);
    for (double& e: original_v) {
        e = dist(gen);
    }

    std::vector<double> v(original_v);

    evaluate_sorting_algorithm("std::sort", std::sort, v.begin(), v.end(), std::less<>{});

    if (n <= 20000) {
        std::copy(original_v.begin(), original_v.end(), v.begin());

        evaluate_sorting_algorithm("insertion sort", insertion_sort, v.begin(), v.end(), std::less<>{});
    }

    std::copy(original_v.begin(), original_v.end(), v.begin());

    evaluate_sorting_algorithm("sequential quicksort", quick_sort, v.begin(), v.end(), std::less<>{});

    std::copy(original_v.begin(), original_v.end(), v.begin());

    evaluate_sorting_algorithm("parallel quicksort", parallel_quicksort_entry, v.begin(), v.end(), std::less<>{});

    return 0;
}
