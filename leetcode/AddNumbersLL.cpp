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
#include <vector>

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
    ListNode* addZeros (ListNode *start , size_t n) {
        if (n <= 0){
            return start;
        }
        ListNode* result = new ListNode(0);
        result->next = addZeros(start, n-1);
        return result;
    }
    void deleteZeroNodes (ListNode *start , size_t n) {
        if (n > 0) {
            deleteZeroNodes(start->next, n-1);
            delete start;
        }
    }

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        size_t len1 = getLength(l1),
                len2 = getLength(l2);

        ListNode * l1tmp, *l2tmp;
        if(len1 > len2){
            l1tmp = l1;
            l2tmp = addZeros(l2, len1 - len2);
        } else {
            l1tmp = addZeros(l1, len2 - len1);
            l2tmp = l2;
        }
        ListNode* prev = addRecursively(l1tmp, l2tmp); //assume that prev->val may have overflow
        ListNode* ans;
        if(prev->val >= 10){
            ans = new ListNode(prev->val / 10);
            ans->next = prev;
            prev->val %= 10;
        } else {
            ans = prev;
        }
        if(len1 > len2){
            deleteZeroNodes(l2tmp, len1 - len2);
        } else {
            deleteZeroNodes(l1tmp, len2 - len1);
        }
        return ans;
    }

    static ListNode* makeList(const vector<int>& vals){
        ListNode* ans = nullptr;
        for(auto it = vals.crbegin(); it != vals.crend(); ++it){
            ListNode* tmp = new ListNode(*it);
            tmp->next = ans;
            ans = tmp;
        }
        return ans;
    }

    static void printList(const ListNode* l){
        if(!l){
            cout << "<NULL>";
        } else {
            cout << "[" << l->val << "]-->";
            printList(l->next);
        }

    }

private:
    //assuming the same length!
    ListNode *addRecursively (const ListNode *l1 , const ListNode *l2) {
        if(!l1->next){
            return new ListNode(l1->val + l2->val);
        }
        ListNode* prev = addRecursively(l1->next, l2->next);
        int carry = prev->val / 10;
        prev->val %= 10;
        ListNode* ans = new ListNode(l1->val + l2->val + carry);
        ans->next = prev;
        return ans;
    }

    ListNode *addMissingNodes (const ListNode *begin, const ListNode *end , ListNode *sum) {
        ListNode* newSum;
        if(begin == end){
            if(sum->val >= 10){
                newSum = new ListNode(sum->val/10);
                sum->val %= 10;
                newSum->next = sum;
                return newSum;
            }
            return sum;
        }
        ListNode* prevSum = addMissingNodes(begin->next, end, sum);
        int newSumVal = begin->val + prevSum->val;
        newSum = new ListNode(newSumVal / 10);
        prevSum->val = newSumVal % 10;
        newSum->next = prevSum;
        return newSum;
    }

    size_t getLength (ListNode *n) {
        return (n ? 1 + getLength(n->next) : 0);
    }

    ListNode *fastForward (ListNode *n , size_t i) {
        for(size_t j=0; j<i; j++){
            n = n->next;
        }
        return n;
    }

};

int main(){
    cout << "Add Numbers that are in Linked Lists\n\n";

/*
    Input: (7 -> 2 -> 4 -> 3) + (5 -> 6 -> 4)
    Output: 7 -> 8 -> 0 -> 7
*/
    Solution s;
    ListNode* l1 = s.makeList({7,2,4,3}),
            *l2 = s.makeList({5,6,4});
    cout << "\nl1:\n";
    s.printList(l1);
    cout << "\nl2:\n";
    s.printList(l2);

    ListNode *sum = s.addTwoNumbers(l1, l2);
    cout << "\nsum:\n";
    s.printList(sum);

    l1 = s.makeList({5});
    l2 = s.makeList({5});
    cout << "\nl1:\n";
    s.printList(l1);
    cout << "\nl2:\n";
    s.printList(l2);
    sum = s.addTwoNumbers(l1, l2);
    cout << "\nsum:\n";
    s.printList(sum);

    l1 = s.makeList({0});
    l2 = s.makeList({7,3});
    cout << "\nl1:\n";
    s.printList(l1);
    cout << "\nl2:\n";
    s.printList(l2);
    sum = s.addTwoNumbers(l1, l2);
    cout << "\nsum:\n";
    s.printList(sum);

    l1 = s.makeList({1});
    l2 = s.makeList({9,9});
    cout << "\nl1:\n";
    s.printList(l1);
    cout << "\nl2:\n";
    s.printList(l2);
    sum = s.addTwoNumbers(l1, l2);
    cout << "\nsum:\n";
    s.printList(sum);

    l1 = s.makeList({9,1,6});
    l2 = s.makeList({0});
    cout << "\nl1:\n";
    s.printList(l1);
    cout << "\nl2:\n";
    s.printList(l2);
    sum = s.addTwoNumbers(l1, l2);
    cout << "\nsum:\n";
    s.printList(sum);

    return 0;
}