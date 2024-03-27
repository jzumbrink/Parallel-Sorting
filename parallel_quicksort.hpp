#pragma once

#include <omp.h>
#include <thread>
#include <cmath>
#include <future>
#include "sequential_quicksort.hpp"

const int PROCESSOR_COUNT = std::thread::hardware_concurrency();

template<class It, class Comp>
void parallel_quicksort(It begin, It end, Comp comp, int depth, std::promise<bool> &finished) {
    if (std::pow(2, depth) <= PROCESSOR_COUNT && std::distance(begin, end) > 1) {
        // parallel section
        It split = partition_vector(begin, end, comp);
        std::promise<bool> finished1;
        std::promise<bool> finished2;

        std::future<bool> f1 = finished1.get_future();
        std::future<bool> f2 = finished2.get_future();

        std::thread t1(parallel_quicksort<It, Comp>, begin, split, comp, depth+1, std::ref(finished1));
        std::thread t2(parallel_quicksort<It, Comp>, split, end, comp, depth+1, std::ref(finished2));

        t1.detach();
        t2.detach();

        f1.wait();
        f2.wait();
    } else {
        quick_sort(begin, end, comp);
    }

    finished.set_value_at_thread_exit(true);
}

template<class It, class Comp>
void parallel_quicksort_entry(It begin, It end, Comp comp) {
    std::promise<bool> f;
    parallel_quicksort(begin, end, comp, 0, f);
}