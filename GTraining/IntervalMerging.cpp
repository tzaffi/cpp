//
// Created by zeph on 12/21/16.
//

/**
Merge Ranges - a phone Interview I kind of failed at with at F l a t i r o n (trying to avoid google'ability)
____________

INPUT: A list of closed integer ranges (allowing for singletons).
OUTPUT: Merge them

E.g.
[(1,4), (8,12), (3,6), (10,15)]

--->

[(1,6), (8,15)]

Some answers:
Can a range consist of a single point, e.g. (4,4)?
    YES!

Can a range be poorly defined. e.g. (4, 2)?
    NO.
**/
#include <tuple>
#include <vector>
#include <iostream>
#include <set>
using namespace std;

using range = pair<int, int>;

class Ranges {
public:
    static set<range> merge(const vector<range>& vr){
        const set<range> sr(vr.cbegin(), vr.cend());
        set<range> result;
//        doAlgo(vr.cbegin(), vr.cend(), res);
        if(sr.size() == 0){
            return result;
        }
        auto iter = sr.cbegin();
        range prev = *iter;
        while(++iter != sr.cend()){
            range curr = *iter;
            if(prev.second < curr.first){
                result.insert(prev);
                prev = curr;
            } else {
                prev = range(prev.first, max(prev.second, curr.second));
            }
        }
        result.insert(prev);
        return result;
    }

    static set<range> makeSet(const vector<range>& v){
        return set<range>(v.cbegin(), v.cend());
    }
//private:
//    static void doAlgo(const vector<range>::const_iterator& left, const vector<range>::const_iterator& right,
//                        set<range>& res) {
//        if(left == right){return;}
//        if(res.empty()){
//            res.insert(*left);
//            return doAlgo(left+1, right, res);
//        }//must need to merge:
//        auto itr_and_inserted = res.insert(*left);
//        if(itr_and_inserted.second){
//            //cases:
//            //1. Disjoint from left and right - recursively call the case [left = left+1]
//            //2. Not disjoint from one or both -
//            //     a. delete those intervals that are touching including this one
//            //     b. merge appropriate
//            //     c. call again (set is not smaller so made a recursive advancement)
//            auto inserted = itr_and_inserted.first;
//            auto inserted_minus_1 = (inserted == res.begin() ? res.end() : inserted - 1);
//            auto inserted_plus_1 = inserted + 1;
//            bool leftDisjoint = (inserted_minus_1 == res.end() || inserted_minus_1->second < inserted->first);
//            bool rightDisjoint = (inserted_plus_1 == res.end() || inserted->second < inserted_plus_1->first);
//            if(leftDisjoint && rightDisjoint){
//                return doAlgo(left+1, right, res);
//            } else if (leftDisjoint && !rightDisjoint){
//                range mergeRight(inserted_minus_1->first, left->second)
//                res.erase(inserted);
//                res.insert(range(, left->second));
//                res.erase(inserted_minus_1);
//                return doAlgo(left+1, res);
//            } else if (!rightDisjoint && leftDisjoint){
//                res.erase(inserted);
//                res.insert(range(left->first, inserted_plus_1->second));
//                res.erase(inserted_minus_1);
//                return doAlgo(left+1, res);
//        } else{}
//
//
//        }
//    }
};

int main(){
    vector< pair< vector<range>, vector<range> > > testCases({
        pair<vector<range>, vector<range> >(
                { range(1,4), range(8,12), range(3,6), range(10,15) },
                { range(1,6), range(8,15)})
     , pair<vector<range>, vector<range> >(
         { range(1,4), range(8,12), range(9,10), range(3,6), range(10,10), range(11,11), range(10,15) },
         { range(1,6), range(8,15)})
     , pair<vector<range>, vector<range> >(
        { range(1,4), range(-5,0), range(-1, 3), range(6,6), range(-4,-4), range(-1, 2) },
        { range(-5,4), range(6,6)})
    });

    cout << "Merge Interval Ranges.\n\n TEST CASES:\n\n";
    for(auto testCase: testCases){
        auto input = testCase.first, output = testCase.second;
        cout << "INPUT: [ ";
        for(auto rng: input){ cout << "( " << rng.first << " , " << rng.second << " ), "; }
        cout << "]\n\nOUTPUT: [ ";
        for(auto rng: output){ cout << "( " << rng.first << " , " << rng.second << " ), "; }
        cout << "]\n\n";
    }

    cout << "\n\nTest Ranges::makeSet()\n";
    for(auto testCase: testCases) {
        auto setTest = Ranges::makeSet(testCase.first);
        cout << "{ ";
        for (auto e: setTest) { cout << "( " << e.first << " , " << e.second << " ), "; }
        cout << "}\n\n";
    }

    cout << "\n\nTest insert ( 9, 10 ):\n";
    range toInsert(9,10);
    for(auto testCase: testCases) {
        auto setTest = Ranges::makeSet(testCase.first);
        cout << "Insert (9,10) in { ";
        for (auto e: setTest) { cout << "( " << e.first << " , " << e.second << " ), "; }
        cout << boolalpha << "}\n";
        auto itr_n_inserted = setTest.insert(toInsert);
        cout << "Insert? " << itr_n_inserted.second << endl;
        cout << "Result of insertion: { ";
        for (auto e: setTest) { cout << "( " << e.first << " , " << e.second << " ), "; }
        cout << "}\n\n";
    }

    cout << "\n\nTest merge:\n";
    for(auto testCase: testCases) {
        auto setTest = Ranges::makeSet(testCase.first);
        cout << "Merge [ ";
        for (auto e: testCase.first) { cout << "( " << e.first << " , " << e.second << " ), "; }
        cout << "]\nResult: { ";
        for (auto e: Ranges::merge(testCase.first) ) { cout << "( " << e.first << " , " << e.second << " ), "; }
        cout << "}\nExpected: { ";
        for (auto e: testCase.second) { cout << "( " << e.first << " , " << e.second << " ), "; }
        cout << "}\n\n";
    }

    return 0;
}
