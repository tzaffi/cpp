//
// Created by zeph on 11/26/16.
//

#include <iostream>

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



template <typename T, typename TComparator>
ArrayHeap<T, TComparator>::ArrayHeap (size_t capacity) :
        capacity(capacity)
{
    std::cout << "Welcome to ArrayHeap of size " << capacity << std::endl;
}

template <typename T, typename TComparator>
size_t ArrayHeap<T, TComparator>::size() const {return m_size;}

template <typename T, typename TComparator>
T ArrayHeap<T, TComparator>::operator[] (size_t i) const {
    return heap[i];
}

template <typename T, typename TComparator>
void ArrayHeap<T, TComparator>::insert (T t) {
    if(capacity >= size()){
        throw CapacityError();
    }
    heap[m_size++] = t;
    throw "NOT IMPLEMENTED";
}

class ArrayHeapTest{
    struct stringCompare{
        bool operator() (const std::string& lhs, const std::string& rhs){
            return lhs < rhs;
        }
    };

    void testCtor(){
        ArrayHeap<std::string, stringCompare> h(100);
    }
};

int dummyMain(){

    return 0;
}