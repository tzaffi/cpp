//
// Created by zeph on 11/27/16.
//
#include <iostream>
#include <set>

using namespace std;

struct standardComparison {
    bool operator() (const int& lhs, const int& rhs) const
    {return lhs<rhs;}
};
struct reverseComparison {
    bool operator() (const int& lhs, const int& rhs) const
    {return lhs>rhs;}
};

template<typename C>
struct heap{
    int peek() const{
        return *_heap.cbegin();
    }
    int pop(){
        auto it = _heap.begin();
        int res = *it;
        _heap.erase(it);
        return res;
    }
    bool isEmpty() const{ return size() == 0;}
    size_t size() const{ return _heap.size(); }
    void insert(const int& x){ _heap.insert(x); }
private:
    multiset<int, C> _heap;
};
using MaxHeap = heap<reverseComparison>;
using MinHeap = heap<standardComparison>;

class MedianFinder {
public:
    // Adds a number into the data structure.
    void addNum(int num) {
        if(isEmpty()){ minHeap.insert(num);}
        else if(isBalanced()){
            if(num >= maxHeap.peek()){ minHeap.insert(num); }
            else {
                minHeap.insert(maxHeap.pop());
                maxHeap.insert(num);
            }
        } else {
            if(num <= minHeap.peek()){ maxHeap.insert(num); }
            else{
                maxHeap.insert(minHeap.pop());
                minHeap.insert(num);
            }
        }
        /* TOO SLOW
        S.insert(num);
        */
    }

    // Returns the median of current data stream
    double findMedian() {
        if(isEmpty()) {return 0;}
        if(isBalanced()){ return (minHeap.peek() + maxHeap.peek())/2.0; }
        return minHeap.peek();
        /* TOO SLOW
        size_t N = S.size();
        if(N == 0){ return 0;}
        auto iter = S.cbegin();
        advance(iter, N/2);
        int middle = *iter;
        if(N%2){ return middle; }
        std::advance(iter,-1);
        return (middle + *iter)/2.0;
        */
    }
private:
    MinHeap minHeap;
    MaxHeap maxHeap;
    bool isEmpty(){ return minHeap.isEmpty(); }
    bool isBalanced(){ return minHeap.size() == maxHeap.size(); }
    /* TOO SLOW
    multiset<int> S;
    */
};

// Your MedianFinder object will be instantiated and called as such:
// MedianFinder mf;
// mf.addNum(1);
// mf.findMedian();

int main(){
    cout << "Streaming Media with two heaps\n\n";
    MinHeap minHeap;
    MaxHeap maxHeap;
    for(int i=1; i<=10; i++){
        maxHeap.insert(i);
        minHeap.insert(i);
    }

    cout << "\nMaxheap:\n";
    while(!maxHeap.isEmpty()){
        cout << maxHeap.pop() << ", ";
    }

    cout << "\nMinheap:\n";
    while(!minHeap.isEmpty()){
        cout << minHeap.pop() << ", ";
    }

    MedianFinder s;
    cout << "\n\nmedian = " << s.findMedian() << endl;
    s.addNum(1);
    cout << "median = " << s.findMedian() << endl;
    s.addNum(2);
    cout << "median = " << s.findMedian() << endl;
    s.addNum(3);
    cout << "median = " << s.findMedian() << endl;

    return 0;
}