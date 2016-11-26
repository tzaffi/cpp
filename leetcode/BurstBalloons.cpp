//
// Created by zeph on 11/24/16.
//
/*
Burst Balloons

Difficulty: Hard

Given n balloons, indexed from 0 to n-1. Each balloon is painted with a number on it represented by array nums. You are asked to burst all the balloons. If the you burst balloon i you will get nums[left] * nums[i] * nums[right] coins. Here left and right are adjacent indices of i. After the burst, the left and right then becomes adjacent.

Find the maximum coins you can collect by bursting the balloons wisely.

Note:
(1) You may imagine nums[-1] = nums[n] = 1. They are not real therefore you can not burst them.
(2) 0 ≤ n ≤ 500, 0 ≤ nums[i] ≤ 100

Example:

Given [3, 1, 5, 8]

Return 167

    nums = [3,1,5,8] --> [3,5,8] -->   [3,8]   -->  [8]  --> []
   coins =  3*1*5      +  3*5*8    +  1*3*8      + 1*8*1   = 167
Credits:
Special thanks to @dietpepsi for adding this problem and creating all test cases.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

#include "../helpers/coutFriends.cpp"

using namespace std;

class Solution {
public:
    //TOO SLOW!!!!
    int maxCoins(vector<int>& nums) {
        if(nums.size() == 0){
            return 0;
        }
        int ans = 0;
        for(unsigned balloonIndex = 0; balloonIndex < nums.size(); balloonIndex++){
            vector<int> burstNums(nums);
            int burstVal = burstValue(burstNums, balloonIndex);
            burstNums.erase(burstNums.begin() + balloonIndex);
            int ansTry = burstVal + maxCoins(burstNums);
            if(ansTry > ans){
                ans = ansTry;
            }
        }
        return ans;
    }
    int burstValue(vector<int>& nums, unsigned balloonIndex){
        int prev = (balloonIndex <= 0 ? 1 : nums[balloonIndex-1]);
        int next = (balloonIndex+1 >= nums.size() ? 1 : nums[balloonIndex+1]);
        return prev * next * nums[balloonIndex];
    }
};

int main() {
    cout << "Burst Balloons\n\n";
    vector<int> testCase{3, 1, 5, 8};
    cout << "Test case is:\n" << testCase << endl << endl;
    cout << endl << endl;
    Solution s;
    cout << "Solution is:\n" << s.maxCoins(testCase) << endl << endl;
    return 0;
}