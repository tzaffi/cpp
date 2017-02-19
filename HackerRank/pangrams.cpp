//
// Created by zeph on 2/18/17.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

/**
 input:
4
we promptly judged antique ivory buckles for the next prize
we promptly judged antique ivory buckles for the prizes
the quick brown fox jumps over the lazy dog
the quick brown fox jump over the lazy dog

 output:
 0101
 */

const unsigned ALPHSIZE = 26;
bool isPangram(const string& s){
    vector<bool> indicator(ALPHSIZE, false);
    unsigned distincts = 0;
    for(const char& c: s){
        if(c != ' ' && !indicator[c-'a']){
            ++distincts;
            if(distincts == ALPHSIZE){ return true; }
            indicator[c-'a'] = true;
        }
    }
    return false;
}

string isPangram(const vector<string>& testSet){
    string result = "";
    for(const string& s: testSet){
        result += ( isPangram(s) ? '1' : '0' );
    }
    return result;
}

int main() {
    string line;
    getline(cin, line);
    stringstream ss(line);
    unsigned N;
    ss >> N;
    vector<string> testSet;
    for(unsigned i=1; i<=N; ++i){
        getline(cin, line);
        testSet.push_back(line);
    }
    cout << isPangram(testSet);
    return 0;
}