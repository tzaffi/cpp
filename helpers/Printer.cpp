//
// Created by zeph on 11/18/16.
//

#include "Printer.h"
#include <iostream>

template<typename T>
void Printer<T>::prettyPrint(const T *A, std::size_t left, std::size_t right, bool starPivot)
{
    std::string pivChar(starPivot ? "*" : "");
    for(std::size_t it=left; it<right; ++it)
    {
        std::cout << pivChar << it << pivChar << ": " << A[it] << '\t';
        pivChar = "";
    }
    std::cout << std::endl;
}

template<typename T>
void Printer<T>::prettyPrint(const std::vector<T>& V)
{
    Printer<T>::prettyPrint(&V[0], 0, V.size());
}

template<typename T>
void Printer<T>::prettyPrint(const std::pair<T, T> &P) {
    std:: cout << "<" << P.first << ", " << P.second << ">";
}


template<typename T>
void Printer<T>::prettyPrint(const std::set<T> &S)
{
    unsigned pos=0;
    for(auto it= S.cbegin(); it!= S.cend(); ++it, ++pos){
        std::cout << pos << ": " << *it << '\t';
    }
}

template<typename T>
void Printer<T>::prettyPrint(const std::multiset<T> &M) {
    unsigned pos=0;
    for(auto it= M.cbegin(); it!= M.cend(); ++it, ++pos){
        std::cout << pos << ": " << *it << '\t';
    }
}
