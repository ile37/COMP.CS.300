#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


/**
 * @brief Erases every second item from the vector. Example: {1, 2, 3, 4} -> {1, 3}
 *
 * @param vec vector where every second item is erased.
 */
void eraseEverySecond(std::vector<int>& vec) {

    auto beg = vec.begin();
    auto end = vec.end();

    for (auto i = end-1; i != beg - 1; i = i-2) {
        vec.erase(i);

    }
}

