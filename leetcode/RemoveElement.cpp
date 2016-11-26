//
// Created by zeph on 11/25/16.
//
/**
 * Combination Sum IV
Remove Element
Difficulty: Easy

Given an array and a value, remove all instances
 of that value in place and return the new length.

Do not allocate extra space for another array, you must do this in place with
 constant memory.

The order of elements can be changed. It doesn't matter what you
 leave beyond the new length.

Example:
Given input array nums = [3,2,2,3], val = 3

Your function should return length = 2, with the first two elements of nums being 2.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int back = 0;
        for(size_t cursor = 0; cursor < nums.size(); ++cursor){
            if(nums[cursor] != val){
                nums[back++] = nums[cursor];
            }
        }
        return back;
    }
};

int main() {
    cout << "Remove Element\n\n\n";

    vector<int> nums = {3,2,2,3};
    int target = 3;
    Solution s;
    int ans = s.removeElement(nums, target);
    cout << "got " << ans << " solutions\n\n";
    assert(ans == 2);

    return 0;
}