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

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode(int x) : val(x), next(NULL) {}

    void printEntireList() const {
        cout << "[" << val << "]->";
        if(next == NULL){
            cout << "NULL";
        } else {
            next->printEntireList();
        }
    }
};

ListNode* getTestCase(unsigned skipValue=1){
    ListNode* root = new ListNode(0);
    ListNode* curr = root;
    for(int i=skipValue; i<= 10*skipValue; i+=skipValue){
        curr->next = new ListNode(i);
        curr = curr->next;
    }
    return root;
}

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* tmp = new ListNode(-1), *m = tmp;
        while(l1 || l2){
            m->next = new ListNode(-1);
            m = m->next;
            if(!l1){
                m->val = l2->val;
                l2 = l2->next;
            }else if(!l2 || l1->val <= l2->val){
                m->val = l1->val;
                l1 = l1->next;
            }else{
                m->val = l2->val;
                l2 = l2->next;
            }
        }
        ListNode* ans = tmp->next;
        delete tmp;
        return ans;
    }
};

int main() {
    cout << "Linked List Merging\n\n";
    ListNode *list_skip1 = getTestCase(),
            *list_skip5 = getTestCase(5);

    cout << "Test case skip 1 is:\n";
    list_skip1->printEntireList();

    cout << "\n\nTest case skip 5 is:\n";
    list_skip5->printEntireList();
    cout << endl << endl;
    Solution s;
    ListNode* ans = s.mergeTwoLists(list_skip1, list_skip5);
    if(ans){
        cout << "\n\nSOLUTION is:\n";
        ans->printEntireList();
    }
    return 0;
}