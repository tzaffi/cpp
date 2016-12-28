//
// Created by zeph on 12/26/16.
//

#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

/**
 * This is the one that caused me the most trouble (took me a while to get it going and didn't finish
 * in time)
 *
 * Given:L
 *  a - a sorted array of ints of size M,
 *  b - a sorted array of ints of size M with with allocated space 2*M,
 *  merge a and b into b
 * @return
 */

//for simplicity's sake use a vector instead of an array:

void fillWithSortedRandom (vector<int> &a , size_t M) {
    for(int i=0; i < M; i++){
        a[i] = rand() % 100;
    }
    sort(a.begin(), a.end());
}

template <typename T>
ostream& operator<<(ostream& os, const vector<T>& v){
    os << "[ ";
    for(auto it = v.cbegin(); it != v.cend(); ++it){ os << *it << ", "; }
    os << "]";
    return os;
}

//template <typename T>
//bool operator==(const vector<T>& lhs, const vector<T> rhs){
//    if (lhs.size() != rhs.size()) return false;
//    for(unsigned i=0; i<lhs.size(); ++i){if (lhs[i] != rhs[i]) return false; }
//    return true;
//}

pair< pair<vector<int>, vector<int>>, vector<int> > makeTestCase(size_t M){
    vector<int> a(M), b(M);
//    cout << "a.size() = " << a.size();
//    cout << "b.size() = " << b.size();
    fillWithSortedRandom(a , M);
    b.insert(b.begin(), a.cbegin(), a.cend());
    fillWithSortedRandom(a , M);
    vector<int> c = a;
    c.insert(c.end(), b.begin(), b.begin()+M);
    sort(c.begin(), c.end());
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "c = " << c << endl;
    return make_pair(make_pair(a,b), c);
}

void merge(const vector<int>& a, vector<int>& b){
    size_t M = a.size();
    if(b.empty()){ return; }
    for(unsigned i=0; i<M; ++i){ b[i+M] = b[i]; }
    size_t a_curs = 0, b_curs = M;
    for(size_t insertIdx = 0; insertIdx < 2*M; ++insertIdx){
//ECONOMIZE:
        if(b_curs >= 2*M || a_curs < M && a[a_curs] < b[b_curs]){
            b[insertIdx] = a[a_curs++];
        } else {
            b[insertIdx] = b[b_curs++];
        }
//TOO LONG-WINDED:
//        if(a_curs < M && b_curs < 2*M){
//            if(a[a_curs] < b[b_curs]){
//                b[insertIdx] = a[a_curs++];
//            } else {
//                b[insertIdx] = b[b_curs++];
//            }
//        }else if(b_curs >= 2*M){
//            b[insertIdx] = a[a_curs++];
//        }else{
//            b[insertIdx] = b[b_curs++];
//        }
    }
    cout << "b = " << b;
}

int main(){
    cout << "-----------Problem 3-----------\n\n";
    for(size_t M=0; M<20; ++M) {
        cout << "<<<<<<<<<< TEST CASE " << M << "<<<<<<<<<<<<<<<\n";
        auto testCase = makeTestCase(M);
        merge(testCase.first.first , testCase.first.second);
        cout << "\ntestCase.second == testCase.first.second ?\n"
             << testCase.second << "==" << testCase.first.second << endl;
        assert(testCase.second == testCase.first.second);
    }
    return 0;
}