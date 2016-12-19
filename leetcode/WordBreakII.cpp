//
// Created by zeph on 12/18/16.
//

/*
Word Break II
Difficulty: Hard

Given a string s and a dictionary of words dict,
add spaces in s to construct a sentence where each word is a valid dictionary word.

Return all such possible sentences.

For example, given
s = "catsanddog",
dict = ["cat", "cats", "and", "sand", "dog"].

A solution is ["cats and dog", "cat sand dog"].
*/

#include <vector>
#include <unordered_set>
#include <string>
#include <iostream>
#include <map>

using namespace std;

class Solution {
public:
    vector<string> wordBreak(string s, unordered_set<string>& wordDict, bool firstTime = true) {
        if(firstTime){ solutions = map<string, vector<string>>(); }
        if(solutions.count(s)){ return solutions[s]; }
        vector<string> soln;
        if(wordDict.count(s)){ soln.push_back(s);}
        for(size_t preflen = s.size()-1; preflen >= 1; --preflen){
            string prefix = s.substr(0, preflen);
            if(wordDict.count(prefix)){
                for(string subsoln: wordBreak(s.substr(preflen), wordDict, false)){
                    soln.push_back(prefix + " " + subsoln);
                }
            }
        }
        solutions[s] = soln;
        return soln;
    }
//    vector<string> wordBreak(string s, unordered_set<string>& wordDict) {
//        solutionMap = {};
//        return runAlgo(s , wordDict , 0);
//    }
private:
    map<string, vector<string>> solutions;
//    map<size_t, vector<string>> solutionMap;
//    vector<string> runAlgo(string s, unordered_set<string>& wordDict, size_t currIndex = 0) {
//        vector<string> res;
//        for (size_t prefixLength=s.size(); prefixLength>=1; --prefixLength){
//            string prefix = s.substr(0, prefixLength);
//            size_t subSolIndex = currIndex + prefixLength - 1;
//            if(wordDict.count(prefix)){
//                if(prefixLength == s.size()){
//                    res.push_back(prefix);
//                } else {
//                    vector<string> subSolution;
//                    if (solutionMap.count(subSolIndex)) {
//                        subSolution = solutionMap[subSolIndex];
//                    } else {
//                        subSolution = runAlgo(s.substr(prefixLength), wordDict, subSolIndex);
//                    }
//                    for (string sol: subSolution) {
//                        res.push_back(prefix + " " + sol);
//                    }
//                }
//            }
//        }
//        solutionMap[currIndex] = res;
//        return res;
//    }
};


int main(){
    Solution sol;

    string s = "catsanddog";
    unordered_set<string> dict = {"cat", "cats", "and", "sand", "dog"};

    vector<string> answer = sol.wordBreak(s, dict);
    unsigned sentCount = 1;
    cout << "answers are:\n";
    for(auto a: answer){
        cout << sentCount << ". " << a << endl;
    }

    s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    dict = {"a","aa","aaa","aaaa","aaaaa","aaaaaa","aaaaaaa","aaaaaaaa","aaaaaaaaa","aaaaaaaaaa"};
    sentCount = 1;
    answer = sol.wordBreak(s, dict);
    cout << "answers are:\n";
    for(auto a: answer){
        cout << sentCount << ". " << a << endl;
    }

    return 0;
}