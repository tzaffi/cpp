//
// Created by zeph on 1/7/17.
//

#include <iostream>
#include <vector>

#include "genericString_3_11_1.h"
/**
Write a generic function to_string that takes an argmuent of an arbitray type (as const&)
and generates a string by piping it to std::stringstream and returning the resulting string.
 **/

int main(){
    using namespace std;
    string x;

    x = to_string("hello");
    cout << "hello? " << x << endl;

    x = to_string(3.1415);
    cout << "3.1415? " << x << endl;

//    x = to_string(make_pair(3,7));
//    cout << "make_pair(3,7)? " << x << endl;
//
//    x = to_string(make_pair(3,"thirteen"));
//    cout << "make_pair(3,\"thirteen\")? " << x << endl;

    vector<int> v({1,2,3,4});
    x = to_string(v);
    cout << "vector<int>({1,2,3,4})? " << x << endl;
}