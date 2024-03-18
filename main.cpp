#include <iostream>
#include <random>
#include <vector>
#include <algorithm>
#include "sequential_quicksort.hpp"
#include "insertion_sort.hpp"

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

    //print_example(v);

    quick_sort(v.begin(), v.end(), std::less<>{});

    //print_example(v);

    const bool sorted = is_sorted(v.begin(), v.end(), std::less<>{});
    std::cout << "Elements are sorted: " << std::boolalpha << sorted << std::endl;

    return 0;
}
