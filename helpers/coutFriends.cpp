//
// Created by zeph on 11/20/16.
//

#include "coutFriends.h"

#include <ostream>
#include <vector>
#include <set>

template<typename containerType>
std::ostream& containerOstreamer(std::ostream& os, const containerType& v)
{
   os << "[";
   size_t pos = 0;
   for (auto ii = v.begin(); ii != v.end(); ++ii, ++pos)
   {
       std::string suffix = (pos == v.size()-1 ? "" : ",\t");
       os << pos << ": " << *ii << suffix;
   }
   os << "]";
   return os;
}

template<typename T>
std::ostream &operator<< (std::ostream &os, const std::vector<T> &v)
{
  return containerOstreamer<std::vector<T>>(os, v);
}


template<typename T>
std::ostream &operator<< (std::ostream &os, const std::set<T> &s)
{
  return containerOstreamer<std::set<T>>(os, s);
}

template<typename T>
std::ostream &operator<< (std::ostream &os, const std::multiset<T> &ms)
{
  return containerOstreamer<std::multiset<T>>(os, ms);
}

template <typename S, typename T>
std::ostream& operator << (std::ostream& os, const std::pair<S, T>& p)
{
   os << "<" << p.first << ", " << p.second << ">";
   return os;
}
