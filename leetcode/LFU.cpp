//
// Created by zeph on 11/26/16.
//

/*
Inspired by [Leetcode](https://leetcode.com/problems/lfu-cache/)
-purportedly and Google Question-
[Wikipeida](https://en.wikipedia.org/wiki/Least_frequently_used),
And this [2010 O(1) Algorithm](http://dhruvbird.com/lfu.pdf)
*/

#include <iostream>
#include <unordered_map>
#include <queue>
#include <chrono>
#include <cassert>

using namespace std;
using namespace std::chrono;

template <typename KeyType, typename ValueType>
struct LFU_Interface {
    LFU_Interface(size_t capacity, ValueType missingSentinel)
            : capacity(capacity), NOT_FOUND(missingSentinel) {}
    virtual void set(const KeyType& key, const ValueType& val) = 0;
    virtual ValueType get(const KeyType& key) = 0;
    virtual size_t size() = 0;

    virtual ~LFU_Interface(){}
    const size_t capacity;
    const ValueType NOT_FOUND;
};

using timeMeasure = time_point<steady_clock, nanoseconds>;
template <typename KeyType, typename ValueType>
struct LFU_Node{
    LFU_Node(KeyType key, ValueType value) : key(key), value(value) {}
    KeyType key;
    ValueType value;
    unsigned long accessCount = 1;

    //TIME STUFF:
    static timeMeasure getTime() {
        return time_point_cast<nanoseconds>(steady_clock::now());
    }
    static const timeMeasure BEGIN_TIME;
    decltype((BEGIN_TIME-BEGIN_TIME).count()) lastAccessTime = (getTime()-BEGIN_TIME).count();
    void tick() {
        accessCount++;
        lastAccessTime = (getTime() - BEGIN_TIME).count();
    }
};
template <typename KeyType, typename ValueType>
const timeMeasure LFU_Node<KeyType, ValueType>::BEGIN_TIME = getTime();

template<typename KeyType , typename ValueType>
ostream &operator<< (ostream &os , const LFU_Node<KeyType , ValueType> &node) {
    os << "key: " << node.key << " value: " << node.value << " accessCount: " << node.accessCount << " lastAccessTime: "
       << node.lastAccessTime;
    return os;
}

template <typename KeyType, typename ValueType>
struct Comparator{
    bool operator() (const LFU_Node<KeyType, ValueType>& lhs, const LFU_Node<KeyType, ValueType>& rhs)
    {
        return lhs.accessCount > rhs.accessCount ||
               ( lhs.accessCount == rhs.accessCount && lhs.lastAccessTime > rhs.lastAccessTime );
    };
};

/****
 * Naive implementation - every action will require a complete re-writing of the priority queue
 * because priority_queue cannot re-heapify in place without poping and/or pushing
 * @tparam KeyType
 * @tparam ValueType
 */
template <typename KeyType, typename ValueType>
class LFU_STL : public LFU_Interface<KeyType, ValueType> {
    using pqType = priority_queue<LFU_Node<KeyType, ValueType>,
            vector<LFU_Node<KeyType, ValueType> >,
            Comparator<KeyType, ValueType> >;
public:
    LFU_STL (size_t capacity, ValueType missingSentinel) :
            LFU_Interface<KeyType, ValueType>(capacity, missingSentinel)
    {}

    virtual size_t size() override {
        return cache.size();
    }

    virtual void set(const KeyType &key, const ValueType &val) override {
        if (values.count(key)) {
            values[key] = val;
            reCachify(key);
        } else {
            if(size() >= LFU_STL::capacity) {
                auto discard = cache.top();
                cout << "Max capacity reached. Size = " << size() << " Discarded:\n" << discard << endl;
                cache.pop();
            }
            cache.emplace(key,val);
            values[key] = val;
        }
    }

    virtual ValueType get(const KeyType& key) override {
        if(!values.count(key)) {
            return this->NOT_FOUND;
        }
        reCachify(key);
        return values[key];
    }

    virtual ~LFU_STL() override {}
private:
    void reCachify (const KeyType &key) {
        pqType newCache;
        while(!cache.empty()){
            auto node = cache.top();
            if (node.key == key){
                node.tick();
            }
            newCache.push(node);
        }
        cache = newCache;
    }

    unordered_map<KeyType, ValueType> values;
    pqType cache;
};

void pqTest(){
    using SNode = LFU_Node<int, int>;
    priority_queue<SNode, vector<SNode>, Comparator<int, int> > pq;
    SNode snodes[5] = {SNode(0,0), SNode(1,1), SNode(2,2), SNode(3,4), SNode(4,4)};
    snodes[2].tick();
    snodes[1].tick();
    snodes[1].tick();
    snodes[1].tick();
    snodes[3].tick();
    snodes[4].tick();
    snodes[4].tick();
    snodes[0].tick();
    cout << "BEFORE:\n";
    for(auto pnode: snodes){
        cout << pnode << endl;
        pq.push(pnode);
    }
    cout << "AFTER:\n";
    while(!pq.empty()){
        cout << pq.top() << endl;
        pq.pop();
    }

    auto whatAmI = SNode::getTime();
    cout << "typeid(whatAmI).name():" << typeid(whatAmI).name() << endl;
    auto whatKindOfDurationAmI = whatAmI - whatAmI;
    cout << "typeid(whatKindOfDurationAmI).name():" << typeid(whatKindOfDurationAmI).name() << endl;
}

int main(){
    cout << "LFU Experimentation\n\n";
    pqTest();

    LFU_STL<string, int> stl(5, INT_MIN);
    assert(stl.capacity == 5);
    assert(stl.get("DNE") == INT_MIN);
    cout << "stl.get(\"DNE\") = " << stl.get("DNE") << endl;
    stl.set("one", 1);
    stl.set("two", 2);
    stl.set("three", 3);
    stl.set("four", 4);
    stl.set("five", 5);
    assert(stl.size() == 5);
    stl.set("six", 6);
    assert(stl.get("one") == stl.NOT_FOUND);
    stl.set("two", 22);
    assert(stl.get("two") == 22);
    for(int i=1; i<=10; i++){
        for(auto x: {"three", "four", "five", "six"}){
            stl.get(x);
        }
    }
    stl.set("fourteen", 14);
    assert(stl.get("two") == stl.NOT_FOUND);

    return 0;
}