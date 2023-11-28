/**
 * iteration2.cc
 *
 * Print every second item of a list starting from the first item
 */

/**
 * DO NOT ADD ANY INCLUDES!!
 */

#include "iteration2.hh"
using namespace std;


void printEverySecond(const list<int>& lst)
{
    int count = 0;
    
    for (auto it = lst.begin(); it != lst.end(); ++it) {
        if (count % 2 == 0) {
            cout << *it << " ";
        }
        count++;
    }
    cout << endl;
}
