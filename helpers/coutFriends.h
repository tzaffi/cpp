//
// Created by zeph on 11/20/16.
//

#ifndef CPP_COUTFRIENDS_H
#define CPP_COUTFRIENDS_H

#include <ostream>
#include <vector>
#include <set>

template <typename T>
std::ostream& operator << (std::ostream& os, const std::vector<T>& v);

template <typename T>
std::ostream& operator << (std::ostream& os, const std::set<T>& s);

template <typename T>
std::ostream& operator << (std::ostream& os, const std::multiset<T>& ms);

template <typename S, typename T>
std::ostream& operator << (std::ostream& os, const std::pair<S, T>& p);

#endif //CPP_COUTFRIENDS_H
