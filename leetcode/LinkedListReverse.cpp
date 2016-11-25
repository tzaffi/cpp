//
// Created by zeph on 11/24/16.
//
/*
Reverse a singly linked list.

click to show more hints.

Hint:
        A linked list can be reversed either iteratively or recursively.
        Could you implement both?
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

/**
 * Definition for singly-linked list.
 */

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

class Solution {
public:
    ListNode* reverseList(ListNode* head, bool useRecursive = true) {
        if(useRecursive) {
            return reverseListRecursively(head);
        } else {
            return reverseListIteratively(head);
        }
    }
private:
    ListNode* reverseListRecursively(ListNode* head){
        if(head == NULL || head->next == NULL){
            return head;
        }
        ListNode* newTail = head->next;
        ListNode* subcase = reverseListRecursively(newTail);
        newTail->next = head;
        head->next = NULL;
        return subcase;
    }
    ListNode* reverseListIteratively(ListNode* head){
        if(head == NULL || head->next == NULL){
            return head;
        }
        ListNode *prev = NULL, *curr = head, *next = head->next;
        do {
            curr->next = prev;
            prev = curr;
            curr = next;
            next = next->next;
        } while(next != NULL);
        curr->next = prev;
        return curr;
    }
};

ListNode* getTestCase(){
    ListNode* root = new ListNode(0);
    ListNode* curr = root;
    for(int i=1; i<= 10; i++){
        curr->next = new ListNode(i);
        curr = curr->next;
    }
    return root;
}

int main() {
    cout << "Linked List Reversal\n\n";
    ListNode* list = getTestCase();

    cout << "Test case is:\n";
    list->printEntireList();

    cout << endl << endl;
    Solution s;
    ListNode* listReversed = s.reverseList(list);
    assert(listReversed != NULL);
    cout << "Recursive reversal is:\n";
    listReversed->printEntireList();

    cout << "\n\nSecond reversal (should be back to previous) is:\n";
    s.reverseList(listReversed)->printEntireList();

    cout << "\n\nThis time reverse iteratively:\n";
    s.reverseList(list, false)->printEntireList();
    return 0;
}