//
// Created by zeph on 11/24/16.
//

/*
Counting Bits
Difficulty: Medium

Given a non negative integer number num.
For every numbers i in the range 0 ≤ i ≤ num calculate
 the number of 1's in their binary representation and return them as an array.

Example:
        For num = 5 you should return [0,1,1,2,1,2].

Follow up:

It is very easy to come up with a solution with run time O(n*sizeof(integer)).
 But can you do it in linear time O(n) /possibly in a single pass?
Space complexity should be O(n).
Can you do it like a boss?
 Do it without using any builtin function like
 __builtin_popcount in c++ or in any other language.
Show Hint
Credits:
        Special thanks to @ syedee for adding this problem and creating all test cases.
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> countBits(int num) {
        if(num == 0) {
            return vector<int>{0};
        }
        int prevNum = pow(2,(int)(log2(num))) - 1;
        vector<int> prevSolution = countBits(prevNum);
        for(unsigned j = prevNum+1; j<=num; ++j){
            prevSolution.push_back(prevSolution[j-(prevNum+1)]+1);
        }
        return prevSolution;
    }
};

int main() {
    cout << "Counting Bits";

    Solution s;
    assert(s.countBits(5) == vector<int>({0,1,1,2,1,2}));
    return 0;
}