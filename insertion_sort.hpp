#pragma once

#include <algorithm>

template <class It, class Comp>
void insertion_sort(It begin, It end, Comp comp) {

    for (It it = begin + 1; it < end; ++it) {
        for (It j = it; j != begin && comp(*j, *(std::prev(j))); j--) {
            std::swap(*j, *(std::prev(j)));
        }
    }
}