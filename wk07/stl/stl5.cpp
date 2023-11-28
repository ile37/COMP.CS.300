#include <iterator>
#include <vector>
#include <algorithm>

#include "test.hh"

using namespace std;


/**
 * @brief Arrange vector in three subsequent sections:
 *        - those divisible by three (asc order)
 *        - those whose reminder is 1 (asc order)
 *        - those whose reminder is 2 (asc order)
 * @param v vector to be sorted
 * @return int EXIT_SUCCESS if everything went OK, EXIT_FAILURE otherwise
 */
int sortMod3(std::vector<int>& v)
{
    auto rem_is_zero = partition(v.begin(), v.end(), [](int a){return a % 3 == 0; });
    auto rem_is_one = partition(rem_is_zero, v.end(), [](int a){return a % 3 == 1; });
    sort(v.begin(), rem_is_zero);
    sort(rem_is_zero, rem_is_one);
    sort(rem_is_one, v.end());
    return EXIT_SUCCESS;
}

