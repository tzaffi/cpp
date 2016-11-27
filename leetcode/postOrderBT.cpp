//
// Created by zeph on 11/25/16.
//

/*
 * Binary Tree Postorder Traversal
Difficulty: Hard

Given a binary tree, return the postorder traversal of its nodes' values.

For example:
Given binary tree {1,#,2,3},
   1
    \
     2
    /
   3
return [3,2,1].

Note: Recursive solution is trivial, could you do it iteratively?
 */

#include <iostream>
#include <vector>
#include <utility>
#include <cassert>
#include <algorithm>
#include <cmath>

#include "../helpers/coutFriends.cpp"

using namespace std;

/**
 * Definition for a binary tree node.
 */

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

struct VisitableTreeNode : public TreeNode {
    VisitableTreeNode(const TreeNode& node)
            : TreeNode(node.val) {
        this->left = node.left;
        this->right = node.right
    }
    bool visited = false;
};

template <typename T>
class Stack{
public:
    void push(T val){
        v.push_back(val);
    }
    bool isEmpty(){
        return v.size() == 0;
    }
    T&& pop(){
        T res = move(v.back());
        v.pop_back();
        return move(res);
    }
private:
    vector<T> v = {};
};

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root, bool recursive = true) {
        return (recursive ? recursivePostorderTraversal(root) : iterativePostorderTraversal(root));
    }
private:
    vector<int> recursivePostorderTraversal(TreeNode* root) {
        vector<int> ans(0);
        if(root->left){
            ans = recursivePostorderTraversal(root->left);
        }
        if(root->right){
            vector<int> rightAns = recursivePostorderTraversal(root->right);
            for(const auto& x: rightAns){
                ans.push_back(x);
            }
        }
        ans.push_back(root->val);
        return ans;
    }

    vector<int> iterativePostorderTraversal (TreeNode *root) {
        vector<int> v;
        if(!root){
            return v;
        }
        Stack<VisitableTreeNode*> s;
        s.push(new VisitableTreeNode(*root));
        while(!s.isEmpty()){
            VisitableTreeNode* n = s.pop();
            if(n->visited){
                v.push_back(n->val);
                delete n;
            } else {
                n->visited = true;
                s.push(n);
                if(n->right) { s.push(new VisitableTreeNode(*n->right)); }
                if(n->left) { s.push(new VisitableTreeNode(*n->left)); }
            }
        }
        return v;
    }

public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == NULL){
            return vector<int>{};
        }
        auto left = inorderTraversal(root->left);
        left.push_back(root->val);
        auto right = inorderTraversal(root->right);
        left.insert(left.end(), right.begin(), right.end());
        return left;
    }

    typedef pair<string, TreeNode*> frame;
    /*
     * The non recursive version uses the general procedure
     * of simulating the recursive stackframe calls with
     * an actuall stack
     */
    vector<int> nonRecursive(TreeNode* root) {
        vector<int> res;
        vector<frame> stack;
        stack.push_back({"do", root});
        while(stack.size()){
            frame currFrame = stack.back();
            stack.pop_back();
            string action = currFrame.first;
            TreeNode* currNode = currFrame.second;
            cout << "currNode = " << currNode->val << endl;
            if(action == "do"){
                TreeNode *left = currNode->left, *right = currNode->right;
                if(right){
                    stack.push_back(frame{"do", right});
                }
                stack.push_back(frame("print", currNode));
                if(left){
                    stack.push_back(frame{"do", left});
                }
            } else { // action == "print"
                cout << "printing = " << currNode->val << endl;
                res.push_back(currNode->val);
            }
        }
        return res;
    }
};

void testStack(){
    Stack<string> s;
    for(auto c: "hello mother"){
        s.push(string(1,c));
    }
    cout << endl << endl;
    while(!s.isEmpty()){
        cout << s.pop();
    }

    Stack<int> s2;
    for(int i=1; i<=10; ++i){
        s2.push(i);
    }
    cout << endl << endl;
    while(!s2.isEmpty()){
        cout << s2.pop();
    }
    cout << endl << endl;
}

void testVisitableTreeNode() {
    TreeNode tn1(15);
    cout << "tn1[" << tn1.val << "] " << endl;
    VisitableTreeNode vtn1(13);
    cout << "vtn1[" << vtn1.val << "] visited = " <<  vtn1.visited << endl;
    VisitableTreeNode vtn2(tn1);
    cout << "vtn2[" << vtn2.val << "] visited = " <<  vtn2.visited << endl;
};

int main() {
    TreeNode one(1), three(3), two(2);
    one.right = &two;
    two.left = &three;

    Solution s;
    cout << s.inorderTraversal(&one) << endl;
    cout << s.nonRecursive(&one) << endl << endl;

    /*

       1
    /    \
    2    4
     \   /\
      3  5 6
          \
           7

SOLUTION: 3, 2, 7, 5, 6, 4, 1
     */
    TreeNode a(1), b(2), c(3), d(4), e(5), f(6), g(7);
    a.left = &b;
    a.right = &d;
    b.right = &c;
    d.left = &e;
    d.right = &f;
    e.right = &g;

    cout << "\n\nINORDER RECURSIVE:\n" << s.inorderTraversal(&a) << endl;
    cout << "\n\nINORDER ITERATIVE:\b" << s.nonRecursive(&a) << endl << endl;
    cout << "\n\nPOST-ORDER RECURSIVE:\b" << s.postorderTraversal(&a) << endl << endl;

    testStack();
    testVisitableTreeNode();

    cout << "\n\nPOST-ORDER NON-RECURSIVE:\b" << s.postorderTraversal(&a, false) << endl << endl;
}