//
// Created by zeph on 2/5/17.
//

/*
Given: A set of positive numbers representing (chlidren's) scores

 E.G: { 100, 73, 88,  99 }

Determine: The minimum number C (for number of candies) which is the sum of
 the optimal allocation (of candies) satisfying the following conditions:
   - each child is allocated at least 1 candy
   - if a child sits to someone with a strictly smaller score, he must get more candy.

E.G. the solution to the above is C = 8 = 2 + 1 + 2 + 3
 because the optimal allocation is
      { 2, 1, 2, 3 }
 */
#include <vector>
#include <iostream>
#include <cassert>

using namespace std;

using testCase_t = pair<vector<unsigned>, unsigned long long>;
vector<testCase_t> testCases{
        testCase_t({100, 73, 88,  99}, 8)
        , testCase_t({100, 73, 88,  99}, 8)
        , testCase_t({100, 101, 102,  103}, 10)
        , testCase_t({103, 102, 101,  100}, 10)
        , testCase_t({100, 100, 88,  88}, 5)
        , testCase_t({100, 101, 101, 102, 103, 103, 104, 105, 104, 103, 102, 102, 101, 101, 101}, 29)
        , testCase_t({101, 101, 101, 102, 102, 103, 104, 105, 104, 103, 103, 102, 101, 101, 100}, 29)
};

unsigned long long solve_wrong(const vector<unsigned>& scores){
    unsigned long long soln = 0;
    if(scores.size() == 1){
        soln = 1;
    } else if(scores.size() == 2) {
        soln = (scores[0] == scores[1] ? 2 : 3);
    } else {
        //traverse in both directions from outside towards center
        soln = 2;
        size_t left_idx = 1, right_idx = scores.size() - 2;
        unsigned left = 1, right = 1;
        soln += (left+right);
        while(left_idx < right_idx) {
            left = (scores[left_idx-1] < scores[left_idx] ? left+1 : 1);
            right = (scores[right_idx] > scores[right_idx+1] ? right+1 : 1);
            soln += (left+right);
            ++left_idx, --right_idx;
        }
        if(left_idx == right_idx) { //the case that we have a middle element
            if(scores[left_idx] > max(scores[left_idx-1], scores[left_idx+1])){
                soln += (max(left,right)+1);
            }else if(scores[left_idx] > scores[left_idx-1]){
                soln += (left+1);
            }else if(scores[left_idx] > scores[left_idx+1]){
                soln += (right+1);
            }else{
                soln += 1;
            }
        } else { //the case of an even number of elements - need to adjust our solution
            left_idx--, right_idx++;
            if(scores[left_idx] < scores[right_idx] && left >= right){
                soln += (left-right+1);
            }else if(scores[left_idx] > scores[right_idx] && left <= right){
                soln += (right-left+1);
            }
        }
    }
    return soln;
}

// critical index is the "bottom" of the scores...
// ...the min of a maximum length strictly monotic streak
size_t findCriticalIndex(const vector<unsigned>& scores){
    ...not worth the effort... maybe later
}

unsigned long long solve(const vector<unsigned>& scores){
    size_t criticalIndex = findCriticalIndex(scores);
    return 0;
}

int main(){
    for(auto testCase : testCases){
        for(auto x : testCase.first){
            cout << x << ", ";
        }
        cout << "\n-----------> " << testCase.second << "\n";
        unsigned long long soln = solve(testCase.first);
        cout << "SOLN = " << soln << "\n";
        assert(testCase.second == soln);
    }
    return 0;
}