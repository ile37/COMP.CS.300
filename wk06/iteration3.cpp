/**
 * iteration3.cc
 *
 * Print beginning half of a list
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration3.hh"
using namespace std;


void printHalf(const list<int>& lst)
{
    auto iter = lst.begin();
    auto half = lst.begin();
    advance(half, distance(lst.begin(), lst.end())/2);
    while(iter != half) {
        cout << *iter << " ";
        ++iter;
    }
    cout << endl;
}

