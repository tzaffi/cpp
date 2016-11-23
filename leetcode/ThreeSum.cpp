//
// Created by zeph on 11/18/16.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
#include <exception>

#include "../helpers/coutFriends.cpp"

/***
From: https://leetcode.com/problems/3sum/

Given an array V of n integers, are there elements a, b, c in V such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example:

```
Given array V = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

At this point, it is probably no easier to solve  N-sum than solving 3-sum specificially.

P(V, N, s):

Given array V, number of summands N, and a target sum s:
Find all distinct N-tuples of V which add up to s.

Pseudocode:

Base case: P(V, 0, s)
  If s = 0: return () the 0-tuple
  Else:     return no-solution

N-1 => N:
  Let T = {}
  For each i in V:
    T = T U {i} X P(V-{i}, N-1, s-i)  // Note that when P(V-{i}, N-1, s-i) is empty, we just skip all processing

Run time analysis: 
STEP N-1 => N:
T(|V|, N) = |V| * T(|V|-1, N-1)
          = |V| * |V-1| * T(|V| - 2, N-2)
.... assuming N < |V|...
          = |V|! / (|V| - N)! = O(|V|^N)

So if the running time is measured in terms of n = |V| with k = number of summands,
this is O(n^k) - which is polynomial time in n with degree k- the number of summands.
****/
//----- MODIFY EVERYTHING BELOW HERE:
/**
 * Input:
 *   nums - T array of summable
 *   target - sum to search for
 *
 * Output:
 *   Indices of first two DISTINCT elements of nums which add up to target
 *     IF THIS EXISTS
 *   pair(0,0) - if these don't exist
 */

using namespace std;
typedef pair<unsigned int, unsigned int> indexPair;

void stdSetTest ();
void stdMultisetTest ();
void setOfMultisetTest();

void directProductTest();
void unionTest();

void testCase0();
void testCase1();
void testCase2();
void testCase3();

template<typename T>
set<multiset<T>> directProduct(const T &lhs, const set<multiset<T>> &rhs)
{
    set<multiset<T>> res;
    for(auto&& ms: rhs) {
        multiset<T> sunion{T(lhs)};
        for(auto&& t: ms) {
            sunion.insert(t);
        }
        res.insert(sunion);
    }
    return res;
}

template<typename T>
set<multiset<T>> operator* (const T &lhs, const set<multiset<T>> &rhs){
  return directProduct(lhs, rhs);
}

template<typename M>
set<M> operator+ (const set<M>& lhs, const set<M>& rhs){
  set<M> U{lhs};
  U.insert(rhs.cbegin(), rhs.cend());
  return U;
}

template<typename T>
set<multiset<T>> NSum(vector<T> V, const size_t& N, const T& target)
{
    if (N == 0)
    {
        return target == 0 ? set<multiset<T>>{{}} : set<multiset<T>>{};
    }
    set<multiset<T>> solutions;
    for(size_t i=0; i<V.size(); i++){
      T curr = V[i];
      vector<T> V_minus_curr(V.begin(), V.begin() + i);
      V_minus_curr.insert(V_minus_curr.end(), V.begin() + i + 1, V.end());
      //cout << "Evaluate NSum(V, N, target) = " << endl;
      //cout << "NSum( " << V_minus_curr << " ,\n" << N-1 << " ,\n" << target-curr << "\n) = " << endl;
      auto subcaseSolutions = NSum(V_minus_curr, N-1, target-curr);
      if(subcaseSolutions.size()) {
        solutions = solutions + (curr * subcaseSolutions);
      }
    }
    return solutions;
    throw runtime_error("Case N = " + to_string(N) + " not yet implement");
}



int main()
{
    stdSetTest();
    stdMultisetTest();
    setOfMultisetTest();

    directProductTest();
    unionTest();
    
    testCase0();
    testCase1();
    testCase2();
    testCase3();

    return 0;
}

void stdMultisetTest () {
    cout << "stdMultisetTest ():" << endl;
    multiset<int> t1{1, 2, 3}, t2{1, 2, 2}, t3{1, 2, 3};
    cout << "t1.size() = "  << t1.size() << endl;
    cout << "t2.size() = "  << t2.size() << endl;
    cout << "t1 = " << endl << t1 << endl;
    cout << endl;
    cout << "t2 = " << endl << t2 << endl;
    cout << "t1 <= t1 = " << boolalpha << (t1 <= t1) << endl;
    cout << "t1 < t2 = " << boolalpha << (t1 < t2) << endl;
    cout << "t2 < t1 = " << boolalpha << (t2 < t1) << endl;
    cout << "t1 == t3 = " << boolalpha << (t1 == t3) << endl;

    multiset<int> empty{};
    cout << "empty.size() = "  << empty.size() << endl;
    cout << "empty = " << endl << empty << endl;
}

void stdSetTest () {
    cout << "stdSetTest ():" << endl;
    set<int> S{1, 4, 3, 1, 2, -7};
    cout << "S.size() = "  << S.size() << endl;
    cout << "S = " << endl << S << endl;
}

void setOfMultisetTest () {
    cout << "setOfMultisetTest ():" << endl;
    set<multiset<int>> empty{{}};
    cout << "empty.size() = "  << empty.size() << endl;
    cout << "empty = " << endl << empty << endl;

    set<multiset<int>> interesting{{1, 2, 0, 1}, {}, {5,4,3,2,1}};
    cout << "interesting.size() = "  << interesting.size() << endl;
    cout << "interesting = " << endl << interesting << endl;
}

void directProductTest()
{
    cout << "directProductTest():" << endl;
    set<multiset<int>> interesting{{1, 2, 0, 1}, {}, {5,4,3,2,1}};
    cout << "directProduct(5,interesting) = " << endl << 5 << " X " << interesting << endl;
    cout << " = " << endl << directProduct(5, interesting) << endl << endl;
    cout << "2 * interesting = " << endl << 2 << " X " << interesting << endl;
    cout << " = " << endl << 2 * interesting << endl << endl;
}

void unionTest()
{
    cout << "unionTest():" << endl;
    set<int> A{1, 3, 5, 7};
    set<int> B{5, 6, 7, 8, 9};
    cout << A << " + " << B << " = " << endl;
    cout << A+B << endl << endl;
}

void testCase0(){
    cout << "testCase0():" << endl;
    vector<int> V{-1, 3, 4, 5, -5};
    int targetSolution = 0, targetNoSolution = 4;
    unsigned N = 0;

    cout << "For V = " << endl << V << endl;
    cout << " and target = " << targetSolution << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, targetSolution) << endl << endl;

    cout << "For V = " << endl << V << endl;
    cout << " and target = " << targetNoSolution << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, targetNoSolution) << endl << endl;
}

void testCase1 ()
{
    cout << "testCase1():" << endl;
    vector<int> V{2, 7, 11, 15};
    size_t N = 1;
    int target = 9;
    cout << "For V = " << endl << V << endl;
    cout << " and target = " << target << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, target) << endl;

    target = 11;
    cout << "For V = " << endl << V << endl;
    cout << " and target = " << target << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, target) << endl;
}

void testCase2 ()
{
    cout << "testCase2():" << endl;
    vector<int> V{2, 7, 11, -2, 15};
    size_t N = 2;
    int target = 9;
    cout << "For V = " << endl << V << endl;
    cout << " and target = " << target << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, target) << endl;

    target = 40;
    cout << "For V = " << endl << V << endl;
    cout << " and target = " << target << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, target) << endl;
}

void testCase3 ()
{
    cout << "testCase2():" << endl;
    vector<int> V{2, 7, 11, -2, 15};
    size_t N = 3;
    int target = 9;
    cout << "For V = " << endl << V << endl;
    cout << " and target = " << target << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, target) << endl;

    target = 40;
    cout << "For V = " << endl << V << endl;
    cout << " and target = " << target << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, target) << endl;

    V = {-1, 0, 1, 2, -1, -4};
    target = 0;
    cout << "For V = " << endl << V << endl;
    cout << " and target = " << target << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;
    cout << NSum(V, N, target) << endl;
}
