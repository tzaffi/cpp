//
// Created by zeph on 11/24/16.
//

/*
Set Matrix Zeroes
Difficulty: Medium

Given a m x n matrix, if an element is 0, set its entire row and column to 0. Do it in place.

click to show follow up.

Follow up:
Did you use extra space?
A straight forward solution using O(mn) space is probably a bad idea.
A simple improvement uses O(m + n) space, but still not the best solution.
Could you devise a constant space solution?
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <cmath>

using namespace std;

class Solution {
public:
    void setZeroes(vector<vector<int>>& matrix) {
        //This is a probabilistically correct algorithm
        const int z{rand()}; //zero marker
        for(unsigned row=0; row< matrix.size(); row++){
            for(unsigned col=0; col< matrix[0].size(); col++){
                if(matrix[row][col] == 0){
                    matrix[row][col] = z;
                }
            }
        }
        for(unsigned row=0; row< matrix.size(); row++){
            for(unsigned col=0; col< matrix[0].size(); col++){
                if(matrix[row][col] == z){
                    for(unsigned i=0; i<matrix[0].size(); i++){
                        if(matrix[row][i] != z){
                            matrix[row][i] = 0;
                        }
                    }
                    for(unsigned i=0; i<matrix.size(); i++){
                        if(matrix[i][col] != z){
                            matrix[i][col] = 0;
                        }
                    }
                }
            }
        }
        for(unsigned row=0; row< matrix.size(); row++){
            for(unsigned col=0; col< matrix[0].size(); col++){
                if(matrix[row][col] == z){
                    matrix[row][col] = 0;
                }
            }
        }
    }
};

int main() {
    srand((unsigned int)time(0));
    cout << "Set Zero Matrix\n\n\n";

    Solution s;
    vector<vector<int>> M({
{1, 2, 3, 4, 5, 0, 7},
{1, 2, 0, 4, 5, 0, 7},
{1, 2, 3, 4, 5, 6, 7},
{1, 2, 3, 0, 5, 6, 7},
{1, 2, 3, 4, 5, 6, 7},
                          });

    vector<vector<int>> N({
{0, 0, 0, 0, 0, 0, 0},
{0, 0, 0, 0, 0, 0, 0},
{1, 2, 0, 0, 5, 0, 7},
{0, 0, 0, 0, 0, 0, 0},
{1, 2, 0, 0, 5, 0, 7},
                          });

    s.setZeroes(M);
    assert(M==N);
    return 0;
}