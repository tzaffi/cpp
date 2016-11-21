//
// Created by zeph on 11/18/16.
//

#include <iostream>
#include <cassert>
#include <vector>
#include <set>
#include "../helpers/Printer.cpp"
#include "../helpers/coutFriends.cpp"

/***
From: https://leetcode.com/problems/3sum/

Given an array S of n integers, are there elements a, b, c in S such that a + b + c = 0? 
Find all unique triplets in the array which gives the sum of zero.

Note: The solution set must not contain duplicate triplets.

For example:

```
Given array S = [-1, 0, 1, 2, -1, -4],

A solution set is:
[
  [-1, 0, 1],
  [-1, -1, 2]
]
```

At this point, it is probably no easier to solve  N-sum than solving 3-sum specificially.

P(S, N, s):

Given array S, number of summands N, and a target sum s:
Find all distinct N-tuples of S which add up to s.

Pseudocode:

Base case: P(S, 0, s)
  If s = 0: return () the 0-tuple
  Else:     return no-solution

N-1 => N:
  Let T = {}
  For each i in S:
    T = T U {i} X P(S-{i}, N-1, s-i)  // Note that when P(S-{i}, N-1, s-i) is empty, we just skip all processing

Run time analysis: 
STEP N-1 => N:
T(|S|, N) = |S| * T(|S|-1, N-1)
          = |S| * |S-1| * T(|S| - 2, N-2)
.... assuming N < |S|...
          = |S|! / (|S| - N)! = O(|S|^N)

So if the running time is measured in terms of n = |S| with k = number of summands,
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
void setOfMultisetTest ();

void testCase0();

//template<typename T>
//indexPair TwoSum(const vector<T>& nums, const T& target) {
//    size_t L = nums.size();
//    for(unsigned i=0; i<L-1; i++){
//        T currTarget = target - nums[i];
//        for(unsigned j=i+1; j<L; j++){
//            if(nums[j] == currTarget)
//                return indexPair(i, j);
//        }
//    }
//    return indexPair(0,0);
//}
//
//template <typename T>
//indexPair runExample(const vector<T> &nums, T target) {
//    cout << "Given: nums = ";
//    Printer<T>::prettyPrint(nums);
//    cout << "\t\t target = " << target << endl;
//
//    auto solution = TwoSum(nums, target);
//    cout << "Solution = ";
//    Printer<T>::prettyPrint(solution);
//    cout << endl;
//    return solution;
//}

int main()
{
    stdSetTest();
    stdMultisetTest();
    setOfMultisetTest();

    testCase0();

//    vector<int> nums = {2, 7, 11, 15};
//    int target = 9;
//
//    indexPair solution = runExample(nums, target);
//    assert(solution.first == 0);
//    assert(solution.second == 1);
//
//    nums = {1,2,3,4,5,6,7,8,9,10};
//    target = 11;
//    solution = runExample(nums, target);
//    assert(solution.first == 0);
//    assert(solution.second == 9);
//
//    target = 14;
//    solution = runExample(nums, target);
//    assert(solution.first == 3);
//    assert(solution.second == 9);
//
//    target = -5;
//    solution = runExample(nums, target);
//    assert(solution.first == 0);
//    assert(solution.second == 0);

    return 0;
}

void stdMultisetTest () {
    multiset<int> t1{1, 2, 3}, t2{1, 2, 2}, t3{1, 2, 3};
    cout << "t1.size() = "  << t1.size() << endl;
    cout << "t2.size() = "  << t2.size() << endl;
    cout << "t1 = ";
    Printer<int>::prettyPrint(t1);
//    cout << "t1 = " << t1 << endl;
    cout << endl;
    cout << "t2 = ";
    Printer<int>::prettyPrint(t2);
    cout << endl;
    cout << "t1 <= t1 = " << boolalpha << (t1 <= t1) << endl;
    cout << "t1 < t2 = " << boolalpha << (t1 < t2) << endl;
    cout << "t2 < t1 = " << boolalpha << (t2 < t1) << endl;
    cout << "t1 == t3 = " << boolalpha << (t1 == t3) << endl;
}

void stdSetTest () {
    set<int> S{1, 4, 3, 1, 2, -7};
    cout << "S.size() = "  << S.size() << endl;
    cout << "S = ";
    Printer<int>::prettyPrint(S);
    cout << endl;
}

void setOfMultisetTest () {
    set<multiset<int>> empty{{}};
}


void testCase0(){
    set<int> S{-1, 3, 4, 5, -5};
    int targetSolution = 0, targetNoSolution = 4;
    unsigned N = 0;

    cout << "For S = ";
    Printer<int>::prettyPrint(S);
    cout << " and target = " << targetSolution << endl;
    cout << "the set of all " << N << "-tuples that sum to target is:" << endl;


    cout << "Vector: " << endl << vector<int>{1,2,3,4,5} << endl;
    cout << "Set: " << endl << set<int>{1,2,3,4,5,-3,-2,-1,0,1,2,3} << endl;
    cout << "Multiset: " << endl << multiset<int>{1,2,3,4,5,-3,-2,-1,0,1,2,3} << endl;
//    set<multiset<int>> solution = NSum(N, S, targetSolution);
//    assert(solution ==  set<multiset<int>>{{}};
}
