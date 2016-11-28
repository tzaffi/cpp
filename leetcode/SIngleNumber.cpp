//
// Created by zeph on 11/27/16.
//

/*
Single Number
Difficulty: Easy

Given an array of integers, every element appears twice except for one. Find that single one.

Note:
        Your algorithm should have a linear runtime complexity. Could you implement it without using extra memory?
*/

#include <iostream>
#include <vector>

#include "../helpers/coutFriends.cpp"

using namespace std;

class Solution {
public:
    int singleNumber(vector<int>& nums) {
        return partition(nums, 0, nums.size());
    }
private:
    int partition(vector<int>& nums, unsigned left, unsigned right){
        if(right == left+1) {return nums[left];}
        unsigned i=left, j=right-1, pivIndex = left + (right - left)/ 2;
        int pivot = nums[pivIndex];
        while(nums[j] >= pivot && j >left) {j--};
        if(j==left){ //pivot is min!!!
            swap(nums[left], nums[pivIndex]);
            int minIndex = -1;
            for(j=left+1; j<right; j++){
                if(nums[j] == pivot){
                    minIndex = j;
                    break;
                }
            }
            if(minIndex == -1){
                return pivot;
            }
            swap(nums[left+1], nums[minIndex]);
            return partition(nums, left+2, right);
        }
        while(nums[i] < pivot) {i++;}

    }
    int partitionBAD(vector<int>& nums, unsigned left, unsigned right){
//        cout << "\nPartitioning from " << left << " to " << right << ": ";
//        for(int k=left; k < right; k++){
//            cout << nums[k] + ", ";
//        }
//        if(left > right){
//            throw "left should be less than right";
//        }
//        if((right-left) % 2 == 0){
//            throw "Should never get here as even sized vectors are illegal";
//        }
        if(right == left+1){
            return nums[left];
        }
        unsigned pivIndex = left + (right - left)/ 2;
        swap(nums[left], nums[pivIndex]);
        int pivot = nums[left];
        unsigned i = left + 1;
        while(i<right-1 && nums[i] < pivot) i++;
        unsigned j = i + 1;
        while(j<right && nums[j] >= pivot) j++;
        while(j<right){
            swap(nums[i], nums[j]);
            while(j<right && nums[j] >= pivot) j++;
            i++;
        }
        swap(nums[left],nums[i-1]);
        if((right-i-1) % 2 == 1) {
            return partition(nums , i-1 , right);
        } else {
            return partition(nums, left, i-1);
        }
    }
};

int main(){
    vector<int> v({1,2,3,4,5,6,7,8,1,2,3,4,5,6,7});
    cout << v << endl;
    swap(v[3], v[5]);
    cout << v << endl;
    Solution s;
    cout << s.singleNumber(v) << endl;

    v = {2,2,1};
    cout << s.singleNumber(v) << endl;

    v={1,0,1};
    cout << s.singleNumber(v) << endl;

    v={17,12,5,-6,12,4,17,-5,2,-3,2,4,5,16,-3,-4,15,15,-4,-5,-6};
    cout << s.singleNumber(v) << endl;
    return 0;
}