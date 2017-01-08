//
// Created by zeph on 1/7/17.
//

#include <sstream>
#include <vector>

#ifndef CPP_GENERICSTRING_3_11_1_H
#define CPP_GENERICSTRING_3_11_1_H

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

#endif //CPP_GENERICSTRING_3_11_1_H
