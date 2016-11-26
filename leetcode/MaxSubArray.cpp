//
// Created by zeph on 11/25/16.
//
/**
 Maximum Subarray
Difficulty: Medium

Find the contiguous subarray within an array (containing at least one number)
 which has the largest sum.

For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
the contiguous subarray [4,-1,2,1] has the largest sum = 6.

click to show more practice.

More practice:
If you have figured out the O(n) solution, try coding another solution using the divide and conquer approach,
 which is more subtle.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int maxSubArray(vector<int>& nums) {
        int ans = *max_element(nums.cbegin(), nums.cend());
        if (ans <= 0){
            return ans;
        }
        int runningSum = 0;
        for(const int& x: nums){
            runningSum += x;
            if(runningSum <= 0){
                runningSum = 0;
            } else if(runningSum > ans){
                ans = runningSum;
            }
        }
        return ans;
    }
};

int main() {
    cout << "Max subarray sum\n\n\n";

    vector<int> nums = {-2,1,-3,4,-1,2,1,-5,4};
    Solution s;
    int ans = s.maxSubArray(nums);
    cout << "got " << ans << " as my answer\n\n";
    assert(ans == 6);

    return 0;
}