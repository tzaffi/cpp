//
// Created by zeph on 11/26/16.
//
#include <iostream>

using namespace std;

class Solution {
public:
    int reverse(int x) {
        int sign = (x<0 ? -1 : 1);
        long y = sign*x;
        string reverse = "0";
        while(y/10){
            reverse += to_string(y%10);
            y = y/10;
        }
        reverse += to_string(y);
        try {
            return stoi(reverse) * sign;
        }catch(...){
            return 0;
        }
    }
};

int main(){
    cout << "Dummy\n\n";
    Solution s;
    cout << s.reverse(1534236469) << endl;
    cout << s.reverse(1) << endl;
}