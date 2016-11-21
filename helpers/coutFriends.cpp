//
// Created by zeph on 11/20/16.
//

#include "coutFriends.h"

#include <ostream>
#include <vector>

//template<typename T>
//std::ostream &operator<< (std::ostream &os , const std::vector<T> &v) {
//    os << "[";
//    size_t pos = 0;
//    for (typename std::vector<T>::const_iterator ii = v.begin(); ii != v.end(); ++ii, ++pos)
//    {
//        std::string suffix = (pos == v.size()-1 ? "]" : ",\t");
//        os << pos << ": " << *ii << suffix;
//    }
//    return os;
//}

template<typename T , template<typename ELEM , typename ALLOC=std::allocator<ELEM> > class Container>
std::ostream &operator<< (std::ostream &o , const Container<T>& container) {
    typename Container<T>::const_iterator ii = container.begin();
    o << "["; // 1
    size_t pos = 0;
    while(ii != container.end())
    {
        std::string suffix = (pos == container.size()-1 ? "]" : ",\t");
        o << pos << ": " << *ii << suffix;
        ++ii;
        ++pos;
    }
    o << " ]"; // 3
    return o;
}
