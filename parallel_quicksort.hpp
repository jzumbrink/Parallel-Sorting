#include <omp.h>
#include <thread>
#include <cmath>
#include "sequential_quicksort.hpp"

const int PROCESSOR_COUNT = std::thread::hardware_concurrency();

template<class It, class Comp>
void parallel_quicksort(It begin, It end, Comp comp, int depth) {
    if (std::pow(2, depth) < PROCESSOR_COUNT && std::distance(begin, end) > 1) {
        // parallel section
        It split = partition_vector(begin, end, comp);
        # pragma omp parallel sections
        {
            #pragma omp section
            {
                parallel_quicksort(begin, split, comp, depth + 1);
            }
            #pragma omp section
            {
                parallel_quicksort(split, end, comp, depth + 1);
            }
        }
    } else {
        quick_sort(begin, end, comp);
    }
}