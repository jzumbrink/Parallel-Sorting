#pragma once

template <class It, class Comp>
It partition_vector(It begin, It end, Comp comp) {
    auto pivot = *(begin);

    It j = end - 1;

    It it = begin + 1;

    while (it != j) {
        if (comp(pivot, *it)) {
            std::swap(*it, *j);
            j--;
        } else {
            it++;
        }
    }

    if (comp(*it, pivot)) {
        std::swap(*it, *begin);
    }

    return it;
}

template <class It, class Comp>
void quick_sort(It begin, It end, Comp comp) {
    if (std::distance(begin, end) > 1) {
        It split = partition_vector(begin, end, comp);
        quick_sort(begin, split, comp);
        if (split != end) {
            quick_sort(split, end, comp);
        }
    }
}
