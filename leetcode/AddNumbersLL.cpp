//
// Created by zeph on 12/1/16.
//

/*
445. Add Two Numbers II
You are given two linked lists representing two non-negative numbers.
 The most significant digit comes first and each of their nodes contain a single digit.
 Add the two numbers and return it as a linked list.

You may assume the two numbers do not contain any leading zero, except the number 0 itself.

Follow up:
What if you cannot modify the input lists? In other words, reversing the lists is not allowed.

Example:

        Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
Output: 7 -> 8 -> 0 -> 7

*/

#include <iostream>

using namespace std;
/**
 * Definition for singly-linked list.
 */
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        size_t len1 = findLength(l1),
                len2 = findLength(l2);

        ListNode * l1tmp, *l2tmp;
        if(len1 > len2){
            l1tmp = fastForward(l1, len1 - len2);
            l2tmp = l2;
        } else {
            l1tmp = l1;
            l2tmp = fastForward(l2, len1 - len1);
        }
        ListNode* prev = addRecursively(l1tmp, l2tmp); //asume that prev->val may have overflow
        // ... to be continued

//        if (!l1->next && !l2->next) {
//            return new ListNode(l1->val + l2->val);
//        }
//        if(l1->next && l2->next){
//            ListNode* prev = addTwoNumbers(l1->next, l2->next);
//            int mostSig = prev->val;
//
//        }
//        if (!l1->next){
//            ListNode* prev = addTwoNumbers(NULL, l2->next);
//            int mostSig = prev->val;
//            prev->val %= 10;
//            ListNode * ans = new ListNode(mostSig/10 + l2->);
//        }
    }
};

int main(){
    cout << "Add Numbers that are in Linked Lists\n\n";
    return 0;
}