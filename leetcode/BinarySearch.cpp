//
// Created by zeph on 12/18/16.
//

/**
Search Insert Position
Difficulty: Medium

Given a sorted array and a target value, return the index if the target is found.
If not, return the index where it would be if it were inserted in order.

You may assume no duplicates in the array.

Here are few examples.
[1,3,5,6], 5 → 2
[1,3,5,6], 2 → 1
[1,3,5,6], 7 → 4
[1,3,5,6], 0 → 0
**/

#include <iostream>
#include <vector>

using namespace std;

class Solution {
public:
    int searchInsert(vector<int>& nums, int target) {
        return binarySearch(nums, target, 0, nums.size());
    }

private:
    int binarySearch(const vector<int>& nums, int target, size_t left, size_t right){
        if( right <= left){ return right; }
        size_t mid = (right + left) / 2;
        if (nums[mid] < target){ return binarySearch(nums, target, mid+1, right); }
        if (nums[mid] > target){ return binarySearch(nums, target, left, mid); }
        return mid;
    }
};

int main(){
    Solution s;

    vector<int> nums = {1,3,5,6};
    int target = 5;
    cout << "first answer is " << s.searchInsert(nums, target) << " which should be 2\n\n";
    target = 2;
    cout << "first answer is " << s.searchInsert(nums, target) << " which should be 1\n\n";
    target = 7;
    cout << "first answer is " << s.searchInsert(nums, target) << " which should be 4\n\n";
    target = 0;
    cout << "first answer is " << s.searchInsert(nums, target) << " which should be 0\n\n";

    return 0;
}