#include <vector>

template <class It, class Comp>
void insertion_sort(It begin, It end, Comp comp) {

    for (It it = begin + 1; it < end; ++it) {
        It j = it;
        while (j != begin && comp(*j, *(std::prev(j)))) {
            auto j_val = *j;
            *j = *(std::prev(j));
            *(std::prev(j)) = j_val;
            j--;
        }
    }
}