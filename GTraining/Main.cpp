//
// Created by zeph on 12/4/16.
//

#include <iostream>
#include "SortedArrayIterator.cpp"

using namespace std;

int main(){
    cout << "GTraiining/Main.cpp " << endl;

    vector<int> a = {0, 2, 4, 6, 8, 10, 12};
    vector<int> b = {0, 3, 6, 9, 12, 15};
    vector<int> res;

    cout << "Start with SortedArrayIterator" << endl;

    cout << "\n\nTry to intersect";
    cout << "\na:\t"; for(auto x: a) cout << x << ", ";
    cout << "\nb:\t"; for(auto x: b) cout << x << ", ";
    res = iterateAndReduce(a, b, Choosers::insertLeftIfEqual, true);
    cout << "\nres:\t"; for(auto x: res) cout << x << ", ";

    a = {3};
    b = {};
    cout << "\n\nTry to intersect";
    cout << "\na:\t"; for(auto x: a) cout << x << ", ";
    cout << "\nb:\t"; for(auto x: b) cout << x << ", ";
    res = iterateAndReduce(a, b, Choosers::insertLeftIfEqual, true);
    cout << "\nres:\t"; for(auto x: res) cout << x << ", ";

    cout << "\n\nNow do Merge sort" << endl;

    return 0;
}