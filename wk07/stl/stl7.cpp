#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh" // NOT_FOUND constant

using namespace std;


/**
 * @brief Find the median value of a given vector, whose elements are in random
 *        order. Return NOT_FOUND if the size of the vector is zero.
 *
 * @param v unsorted vector
 * @return int calculated median of parameter vector
 */
int findMedian(std::vector<int>& v)
{
    int size = v.size();

    if (size == 0) {
        return NOT_FOUND;
    }

    auto v_copy = v;
    sort(v_copy.begin(), v_copy.end());

    if (size % 2 == 0) {
        return ( v_copy[v_copy.size()/2 - 1] + v_copy[v_copy.size()/2] ) / 2;
    } else {
        return v_copy[v_copy.size()/2];
    }
}

