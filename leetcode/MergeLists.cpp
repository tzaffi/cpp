//
// Created by zeph on 11/25/16.
//

/*
Merge Two Sorted Lists
Difficulty: Easy

Merge two sorted linked lists and return it as a new list.
 The new list should be made by splicing together the nodes of the first two lists.
 */

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>
#include "../helpers/coutFriends.cpp"

using namespace std;

class Solution {
public:
    vector<int> mergeTwoLists(const vector<int>& av, const vector<int>& bv) {
        vector<int> mv(av.size()+bv.size());
        auto a = av.cbegin();
        auto b = bv.cbegin();
        auto m = mv.begin();
        while(a != av.cend() || b != bv.end()){
            if(a == av.cend() || (b != bv.cend() && *a > *b)){
                *(m++) = (*b++);
            } else {
                *(m++) = (*a++);
            }
        }
        return mv;
    }
};

int main() {
    cout << "Merge Sorted Lists\n\n";

    vector<int> A = {1, 3, 5, 7, 9};
    vector<int> B = {4, 5, 6, 10, 11};
    cout << "A is:\n" << A << endl << endl;
    cout << "B is:\n" << B << endl << endl;

    Solution s;
    cout << "merge(A,B) is:\n" << s.mergeTwoLists(A,B) << endl << endl;
    return 0;
}