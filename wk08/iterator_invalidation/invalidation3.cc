#include <iterator>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;


/**
 * @brief duplicates even numbers in the vector, removes uneven numbers. Example: {1, 2, 3 4} -> {2, 2, 4, 4}
 *
 * @param vec vector to be handled
 */
void duplicateEvenRemoveUneven(std::vector<int>& vec) {

    using Iter = std::vector<int>::iterator;

    vec.reserve(vec.size()*2);

    Iter begin = vec.begin();
    Iter end = vec.end();

    for ( Iter it = end-1; it != begin-1; it--){
        if ( *it % 2 == 0 ){
            vec.insert(it+1, *it);
        }
        else {
            vec.erase(it);
        }
    }
}

