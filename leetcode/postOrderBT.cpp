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

class Solution {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        return recursivePostorderTraversal(root);
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
}