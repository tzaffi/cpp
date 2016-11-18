//
// Created by zeph on 11/18/16.
//

#include <iostream>
#include <cassert>
#include <vector>
#include "../helpers/Printer.cpp"

/***
From: https://leetcode.com/problems/two-sum/

 Given an array of integers, return **indices** of the
 two numbers such that they add up to a specific target.

You may assume that each input would have exactly one solution.

Example:
```
        Given nums = [2, 7, 11, 15], target = 9,

        Because nums[0] + nums[1] = 2 + 7 = 9,
return [0, 1].
```
****/

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

template<typename T>
indexPair TwoSum(vector<T> nums, T target) {
    size_t L = nums.size();
    for(unsigned i=0; i<L-1; i++){
        T currTarget = target - nums[i];
        for(unsigned j=i+1; j<L; j++){
            if(nums[j] == currTarget)
                return indexPair(i, j);
        }
    }
    return indexPair(0,0);
}

template <typename T>
indexPair runExample(const vector<T> &nums, T target) {
    cout << "Given: nums = ";
    Printer<T>::prettyPrint(nums);
    cout << "\t\t target = " << target << endl;

    auto solution = TwoSum(nums, target);
    cout << "Solution = ";
    Printer<T>::prettyPrint(solution);
    cout << endl;
    return solution;
}

int main()
{
    vector<int> nums = {2, 7, 11, 15};
    int target = 9;

    indexPair solution = runExample(nums, target);
    assert(solution.first == 0);
    assert(solution.second == 1);

    nums = {1,2,3,4,5,6,7,8,9,10};
    target = 11;
    solution = runExample(nums, target);
    assert(solution.first == 0);
    assert(solution.second == 9);

    target = 14;
    solution = runExample(nums, target);
    assert(solution.first == 3);
    assert(solution.second == 9);

    target = -5;
    solution = runExample(nums, target);
    assert(solution.first == 0);
    assert(solution.second == 0);

    return 0;
}