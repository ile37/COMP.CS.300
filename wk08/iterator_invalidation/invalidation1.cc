#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


/**
 * @brief creates a vector with ascending numbers from 0 - n-1
 *
 * @param n the size of the vector to be created
 */
std::vector<int> ascendingVector(int n) {

    std::vector<int> v;
    v.reserve(n);

    auto begin = v.begin();
    for (int i = n-1; i >= 0; --i) {
        v.insert(begin, i);
    }

    return v;
}

