//
// Created by zeph on 1/7/17.
//

#include <iostream>
#include <sstream>
#include <vector>

/**
Write a generic function to_string that takes an argmuent of an arbitray type (as const&)
and generates a string by piping it to std::stringstream and returning the resulting string.
 **/


template<typename T>
std::ostream& operator<< (std::ostream& os, const std::vector<T>& v){
    os << "[ ";
    for(auto x: v){
        os << x << " , ";
    }
    os << "]";
    return os;
};

template <typename T>
std::string to_string(const T& x){
    std::stringstream sstream;
    sstream << x;
    return sstream.str();
}


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