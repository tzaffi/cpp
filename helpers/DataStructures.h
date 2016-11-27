//
// Created by zeph on 11/26/16.
//

#ifndef CPP_DATASTRUCTURES_H
#define CPP_DATASTRUCTURES_H

#include <vector>

struct CapacityError{};

template <typename T, typename TComparator>
class ArrayHeap{
public:
    ArrayHeap(size_t capacity);
    size_t size() const;
    T operator[] (size_t i) const;
    T top(size_t i) const {return operator[](i);}
    void insert(T t);  //heapifies after inserting
    void reset(size_t i, T t); //heapifies after reseting
    T pop();
    //TODO: add heapify method
    static std::vector<T>&& heapSort(const std::vector<T>& v);
    const size_t capacity;

    static const TComparator ltObject;
private:
    size_t m_size = 0;
    std::vector<T> heap;
};


#endif //CPP_DATASTRUCTURES_H
