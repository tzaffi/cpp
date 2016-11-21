//
// Created by zeph on 11/20/16.
//

#ifndef CPP_COUTFRIENDS_H
#define CPP_COUTFRIENDS_H

#include <ostream>
#include <vector>


//template <typename T>
//std::ostream& operator << (std::ostream& os, const std::vector<T>& v);

template <typename T, template<typename ELEM, typename ALLOC=std::allocator<ELEM> > class Container>
std::ostream& operator<< (std::ostream& o, const Container<T>& container);

#endif //CPP_COUTFRIENDS_H
