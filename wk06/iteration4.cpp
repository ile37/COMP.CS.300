/**
 * iteration4.cc
 *
 * Print all items of a list in a reverse order
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration4.hh"
using namespace std;


void printReverse(const list<int>& lst)
{
    list<int>::const_iterator iter = lst.end();
    --iter;
    while (iter != lst.begin()) {
        cout << *iter << " ";
        --iter;
    }
    cout << *iter << endl;
}
