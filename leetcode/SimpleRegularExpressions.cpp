//
// Created by zeph on 11/29/16.
//

/*
Implement regular expression matching with support for '.' and '*'.

'.' Matches any single character.
'*' Matches zero or more of the preceding element.

The matching should cover the entire input string (not partial).

The function prototype should be:
bool isMatch(const char *s, const char *p)

Some examples:
isMatch("aa","a") → false
isMatch("aa","aa") → true
isMatch("aaa","aa") → false
isMatch("aa", "a*") → true
isMatch("aa", ".*") → true
isMatch("ab", ".*") → true
isMatch("aab", "c*a*b") → true
*/

#include <iostream>
#include <cassert>

using namespace std;

class Solution {
public:
    bool isMatch(const string& s, const string& p) {
        if(p.size() == 0){ return s.size() == 0; }
        if(p.size() == 1){
            return s.size() == 1 && (p[0] == '.' || p[0] == s[0]);
        }
        if(p[1] != '*'){
            return s.size() && (p[0] == '.' || p[0] == s[0]) && isMatch(s.substr(1), p.substr(1));
        } // p[1] == '*':
        if(p[0] != '.'){
            return (s.size() && (s[0] == p[0]) && isMatch(s.substr(1), p))
                || isMatch(s,p.substr(2));
        }//p[0] == '.:
        return (s.size() && isMatch(s.substr(1), p)) || isMatch(s,p.substr(2));
    }
};

int main(){
    cout << "Simple Regular Expressions";

    Solution s;

    string pattern = "abcde";
    string test = "abcde";

    assert(s.isMatch(test, pattern));
    assert(s.isMatch("aa","a") == false);
    assert(s.isMatch("aa","aa") == true);
    assert(s.isMatch("aaa","aa") == false);
    assert(s.isMatch("aa", "a*") == true);
    assert(s.isMatch("aa", ".*") == true);
    assert(s.isMatch("ab", ".*") == true);
    assert(s.isMatch("aab", "c*a*b") == true);

    assert(s.isMatch("aa",".*") == true);
    return 0;
}