#include <iostream>
#include <random>
#include <algorithm>
#include "insertion_sort.hpp"

using namespace std;

void print_example(vector<double> &v) {
    cout << "Example" << endl;
    for (double& e: v) {
        cout << e << endl;
    }
    cout << endl;
}

int main() {

    int n;

    cout << "Size of example (leave blank for 10^6):" << endl;
    cin >> n;

    if (n == 0) {
        n = 1000000;
    }

    cout << n << endl;

    random_device r;
    default_random_engine gen(r());
    uniform_real_distribution<double> dist;

    vector<double> v(n);
    for (double& e: v) {
        e = dist(gen);
    }

    print_example(v);

    insertion_sort(v.begin(), v.end(), less<>{});

    print_example(v);

    const bool sorted = is_sorted(v.begin(), v.end(), less<>{});
    cout << "Elements are sorted: " << boolalpha << sorted << endl;

    return 0;
}
