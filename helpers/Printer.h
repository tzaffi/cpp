//
// Created by zeph on 11/18/16.
//

#ifndef CPP_PRINTER_H
#define CPP_PRINTER_H


#include <vector>

template <typename T>
class Printer {
public:
    static void prettyPrint(const std::vector<T>& V);
    static void prettyPrint(const T* A, std::size_t left, std::size_t right, bool starPivot= false);
    static void prettyPrint(const std::pair<T, T>& P);
};


#endif //CPP_PRINTER_H
