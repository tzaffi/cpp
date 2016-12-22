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

using namespace std;

using range = pair<int, int>;

int main(){
    vector< pair< vector<range>, vector<range> > > testCases({
        pair<vector<range>, vector<range> >(
                { range(1,4), range(8,12), range(3,6), range(10,15) },
                { range(1,6), range()})
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
    return 0;
}
