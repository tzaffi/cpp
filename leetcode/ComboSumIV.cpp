//
// Created by zeph on 11/25/16.
//
/**
 * Combination Sum IV
Difficulty: Medium

Given an integer array with all positive numbers and no duplicates,
 find the number of possible combinations that add up to a positive integer target.

Example:

nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
Follow up:
What if negative numbers are allowed in the given array?
How does it change the problem?
What limitation we need to add to the question to allow negative numbers?

Credits:
Special thanks to @pbrother for adding this problem and creating all test cases.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

class Solution {
public:
    int combinationSum4(vector<int>& nums, int target){
        return bruteForce(nums, target);
    }
private:
    int bruteForce(vector<int>& nums, int target){
        int ans = 0;
        if (target <= 0){
            return ans;
        } else if (find(nums.cbegin(), nums.cend(), target) != nums.cend()){
            ans++;
        }
        for(auto& x: nums){
            int newTarget = target - x;
            if( newTarget > 0 ){
                ans += combinationSum4(nums, newTarget);
            }
        }
        return ans;
    }
};

int main() {
    cout << "Combination Sums IV\n\n\n";

    vector<int> nums = {1, 2, 3};
    int target = 4;
    Solution s;
    int ans = s.combinationSum4(nums, target);
    cout << "got " << ans << " solutions\n\n";
    assert(ans == 7);

    nums = {4,2,1};
    target = 32;
    ans = s.combinationSum4(nums, target);
    cout << "got " << ans << " solutions\n\n";
    return 0;
}