//
// Created by zeph on 11/25/16.
//
/**
Missing Number
Difficulty: Medium

Given an array containing n distinct numbers taken from 0, 1, 2, ..., n,
 find the one that is missing from the array.

For example,
Given nums = [0, 1, 3] return 2.

Note:
Your algorithm should run in linear runtime complexity. Could you
 implement it using only constant extra space complexity?

Credits:
Special thanks to @jianchao.li.fighter for adding this problem and
 creating all test cases.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    int missingNumber(vector<int>& nums) {
        return bruteForce(nums);
    }
private:
    int bruteForce(vector<int>& nums) {
        vector<bool> tracker(nums.size()+1, false);
        for(const auto& x: nums){
            tracker[x] = true;
            cout << "tracker[" << x << "] = " << tracker[x] << endl;
        }
        for(int i=0; i<tracker.size(); i++){
            if(!tracker[i])
                return i;
        }
        return -1;
    }
    int cleverButNotWorkingOnLargeInput(vector<int>& nums) {
        unsigned long long factorial = myFactorial(nums.size()+1);
        for (const auto& x: nums){
            factorial /= (x+1);
        }
        return factorial-1;
    }
    inline long long myFactorial (unsigned long n) {
        if(n <= 1){
            return 1;
        }
        long long ans = 1;
        for(unsigned i = 2; i<= n; i++){
            ans *= i;
        }
        return ans;
    }
};

int main() {
    cout << "Missing Number\n\n\n";

    vector<int> nums = {0, 1, 3};
    Solution s;
    int ans = s.missingNumber(nums);
    cout << "got " << ans << " as my answer\n\n";
    assert(ans == 2);

    nums = {45,35,38,13,12,23,48,15,44,21,43,26,6,37,1,19,22,3,11,32,4,16,28,49,29,36,33,8,9,39,46,17,41,7,2,5,27,
            20,40,34,30,25,47,0,31,42,24,10,14};
    ans = s.missingNumber(nums);
    cout << "got " << ans << " as my answer\n\n";
    assert(ans == 18);

    nums = {0};
    ans = s.missingNumber(nums);
    cout << "got " << ans << " as my answer\n\n";
    assert(ans == 1);


    return 0;
}