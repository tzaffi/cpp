//
// Created by zeph on 11/24/16.
//

/*
A sequence of numbers is called a wiggle sequence if the
 differences between successive numbers strictly alternate
 between positive and negative. The first difference (if one exists)
 may be either positive or negative. A sequence with fewer than
 two elements is trivially a wiggle sequence.

For example, [1,7,4,9,2,5] is a wiggle sequence because the differences
 (6,-3,5,-7,3) are alternately positive and negative.
 In contrast, [1,4,7,2,5] and [1,7,4,5,5]
 are not wiggle sequences, the first because its first two
 differences are positive and the second because its last difference is zero.

Given a sequence of integers, return the length of the longest
 subsequence that is a wiggle sequence. A subsequence
 is obtained by deleting some number of elements
 (eventually, also zero) from the original sequence,
 leaving the remaining elements in their original order.

Examples:
        Input: [1,7,4,9,2,5]
Output: 6
The entire sequence is a wiggle sequence.

 WRONG:
Input: [1,17,10,13,10,16,8]
Output: 7
There are several subsequences that achieve this length.
 One is [1,17,10,13,10,16,8].

Input: [1,2,3,4,5,6,7,8,9]
Output: 2
Follow up:
Can you do it in O(n) time?
*/
#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

class Solution {
public:
    int wiggleMaxLength(vector<int>& nums) {
        size_t L = nums.size();
        if(L <= 2){
            return L;
        }
        int currWiggle = nums[1]-nums[0];
        int currWS = (currWiggle == 0 ? 1 : 2), max = currWS;
        for(int i = 1; i+1 < L; i++){
            int nextWiggle = nums[i+1]-nums[i];
            int signTest = currWiggle*nextWiggle;
            if(signTest < 0){
                currWS++;
                if(currWS > max){
                    max = currWS;
                }
            } else if (signTest == 0) {
                currWS = 1;
                i++;
            } else {
                currWS = 2;
            }
            currWiggle = nextWiggle;
        }
        return max;
    }
};


int main(){
    cout << "WiggleSubsequence.cpp (DID NOT COMPLETE CORRECTLY)\n";

    Solution s;
    vector<int> v{1, 2, 1, 2, 3, 2, 3, 2, 3, 2, 3};
    assert(s.wiggleMaxLength(v) == 8);
    return 0;
}