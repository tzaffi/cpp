//
// Created by zeph on 12/26/16.
//

#include <iostream>
#include <unordered_set>
#include <vector>
#include <set>

using namespace std;

/**
 *
 * There is a clever algorithm for computing the number of distinct substrings of s,
 * Call this X(S)
The main idea is to count the number of distinct substrings as
    the number of distinct PREFIXES of all the SUFFIXES of s.

So if N = |s| we have

 X(s) = Number of substrings - Number of duplications
      = N*(N+1)/2 - Number of duplications.

 The clever algorithm figures out how to count the Number of duplications, call this D(s).
 Since a substring is a prefix of a suffix, we need only find duplicates of prefixes within
 suffixes which we can sort for ease of comparison. Then compare each consecutive pair of strings
 finding the longest common prefix and subtract this value out. In other words:

 X(S) = N*(N+1)/2 - SUM(i=0, i<=N-1) |LCP(SUFF(i), SUFF(i+1))|

 where SUFF[i] is the i'th suffix of S in lexicographic order


 TO FIND AN OPTIMAL SOLUTION, INSTEAD OF USING ORDERED SUFFIXES, USE A SUFFIX TRIE...

 *
 * @return
 */

#include <memory>

struct TrieNode{
    TrieNode(unsigned label) : label(label) {}
    const unsigned label;
    vector<pair<string, shared_ptr<TrieNode>>> edges;
};

struct DistinctSubstrings{
    DistinctSubstrings(string s) : s(s), L(s.size()) {}

    unsigned long countBruteForce(){
        unordered_set<string> substrings;
        for(unsigned begin=0; begin<s.size(); ++begin){
            for(unsigned len=1; begin + len <= s.size(); ++len){
                substrings.insert(s.substr(begin, len));
            }
        }
        return substrings.size();
    }

    inline unsigned long longestCommonPrefix(const string& a, const string& b){
        unsigned long lcp = 0;
        while(lcp < a.size() && lcp < b.size() && a[lcp] == b[lcp]){
            lcp++;
        }
        return lcp;
    }

    unsigned long countWithSortedSuffixes(){
        set<string> suffixes;
        for(unsigned begin=0; begin < L; ++begin){
            suffixes.insert(s.substr(begin));
        }
        unsigned long dupeCount = 0;
        auto curr = suffixes.cbegin(), next = curr;
        ++next;
        while(next != suffixes.cend()){
            dupeCount += longestCommonPrefix(*curr, *next);
            ++curr;
            ++next;
        }
        return L*(L+1)/2 - dupeCount;
    }

//O(N^2) algorithm
    void buildSuffixTrieNaively(){
        //too complicated so abandoned for now
//        string t = s + '$';
//        unsigned label = 0;
//        suffixTrie = shared_ptr<TrieNode>{new TrieNode(label++)};
//        //not building the path for auxilliary suffix "$":
//        for(unsigned left=0; left < L; ++left){
//            string suffix = t.substr(left);
//            TrieNode currNode = *suffixTrie;
//            while(suffix.size()) {
//                string traversalKey = getTraversalKey(suffix , currNode);
//                if (!traversalKey.size()) {
//                    currNode.edges.push_back(make_pair(suffix , shared_ptr<TrieNode>{label++}));
//                    suffix = "";
//                } else {
//                    string prefix = longestCommonPrefix(traversalKey, suffix);
//
//                }
//
//            }
//        }
    }

private:
    const string s;
    const unsigned long L;
    shared_ptr<TrieNode> suffixTrie;

    string getTraversalKey (const string& suffix, const TrieNode& node) {
        char firstLetter = suffix[0];
        for(const auto& keyPair: node.edges){
            if(firstLetter == keyPair.first[0]){
                return keyPair.first;
            }
        }
        return string();
    }
};


int main(){
    cout << "-----------Distinct Substrings-----------\n\n";
    vector<string> testStrings = {"banana", "aardvark", "aaabaaabaaabaaa"};
    for(string s: testStrings){
        cout << "Testing the number of distinct substrings of '" << s << "':\n";
        DistinctSubstrings ds(s);
        cout << "Brute force: " << ds.countBruteForce() << endl;
        cout << "With sorted suffixes: " << ds.countWithSortedSuffixes() << endl;
    }
    return 0;
}