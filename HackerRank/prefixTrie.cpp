//
// Created by zeph on 2/4/17.
//

/*
We're going to make our own Contacts application! The application must perform two types of operations:

add name, where  is a string denoting a contact name. This must store  as a new contact in the application.
find partial, where  is a string denoting a partial name to search the application for.
 It must count the number of contacts starting with  and print the count on a new line.
Given  sequential add and find operations, perform each operation in order.

Input Format

The first line contains a single integer, , denoting the number of operations to perform.
Each line  of the  subsequent lines contains an operation in one of the two forms defined above.

Constraints

        It is guaranteed that  and  contain lowercase English letters only.
The input doesn't have any duplicate  for the  operation.
Output Format

For each find partial operation, print the number of contact names starting with  on a new line.

Sample Input

4
add hack
add hackerrank
find hac
find hak


Sample Output

2
0
Explanation

        We perform the following sequence of operations:

Add a contact named hack.
Add a contact named hackerrank.
Find and print the number of contact names beginning with hac.
 There are currently two contact names in the application and both of them start with hac, so we print  on a new line.
Find and print the number of contact names beginning with hak.
 There are currently two contact names in the application but neither of them start with hak,
 so we print  on a new line.
 */

#include <cmath>
#include <vector>
#include <map>
#include <iostream>
#include <algorithm>
#include <memory>
using namespace std;


class trieNode{
    friend class prefixTrie;
    map<char, shared_ptr<trieNode>> _next;
    unsigned prefixCount;

public:
    const char val;
    static const trieNode DNE;
    trieNode(char val) : prefixCount(0), val(val) {}
    bool hasNext(char c) const{
        return _next.count(c) > 0;
    }
    const trieNode& operator[](char c) const {
        if(hasNext(c)){
            return *_next.at(c);
        } else {
            return DNE;
        }
    }
    shared_ptr<trieNode>& insert(char c){
        _next[c] = shared_ptr<trieNode>(new trieNode(c));
        return _next.at(c);
    }
    bool isNull() const{
       return this == &trieNode::DNE;
    }
    unsigned numberOfPrefixes() const{
        return prefixCount;
    }
    trieNode& operator++(){
        ++prefixCount;
        return *this;
    }
};
trieNode const trieNode::DNE = trieNode(' ');

ostream& operator << (ostream& os, const trieNode& t){
    if(t.isNull()){ return os << "NULL"; }
    return os << t.val;
}

class prefixTrie{
    shared_ptr<trieNode> root;
public:
    prefixTrie() : root(new trieNode{' '}) {}

    void add(string s){
        shared_ptr<trieNode> curr = root;
        vector<shared_ptr<trieNode>> path;
        path.push_back(curr);
        bool newWord = false;
        for(char c: s){
            if(curr->hasNext(c)){
                curr = curr->_next[c];
            } else {
                curr = curr->insert(c);
                newWord = true;
            }
            path.push_back(curr);
        }
        if(newWord){
            for(auto n: path){
                ++(*n);
//                cout << *n << "<--" << n->numberOfPrefixes();
            }
//            cout << endl;
        }
    }

    unsigned find (string s) {
        shared_ptr<trieNode> curr = root;
//        cout << endl;
        for(char c: s){
//            cout << c << ":" << curr->numberOfPrefixes() << ", ";
            if(!curr->hasNext(c)){
                return 0;
            }
            curr = curr->_next[c];
        }
        return curr->numberOfPrefixes();
    }
};

int basic_test() {
    trieNode t1('a');
    cout << "t1 = " << t1 << endl;
    cout << "BEFORE t1['b'] = " << t1['b'] << endl;
    t1.insert('b');
    cout << "AFTER t1['b'] = " << t1['b'] << endl;
    cout << "BUT t1['c'] = " << t1['c'] << endl;
    cout << "t1.numberOfPrefixes() = " << t1.numberOfPrefixes() << endl;
    ++t1;
    cout << "t1.numberOfPrefixes() = " << t1.numberOfPrefixes() << endl;
    cout << "++t1.numberOfPrefixes() = " << (++t1).numberOfPrefixes() << endl;
    return 0;
}

int main(){
    prefixTrie T;
    unsigned N;
    cin >> N;
    for(unsigned i=0; i<N; ++i){
        string cmd, word;
        cin >> cmd >> word;
//        cout << "cmd = " << cmd << ", word = " << word << endl;
        if(cmd == "add"){
            T.add(word);
        } else {
            cout << T.find(word) << endl;
        }
    }
    //return basic_test();
    return 0;
}