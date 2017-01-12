//
// Created by zeph on 1/11/17.
//

/***********
Kundu is true tree lover. Tree is a connected graph having N vertices and N-1 edges.
 Today when he got a tree, he colored each edge with one of either red(r) or black(b) color.
 He is interested in knowing how many triplets(a,b,c) of vertices are there , such that, there is at
 least one edge having red color on all the three paths i.e. from vertex a to b, vertex b to c and vertex c to a .
 Note that (a,b,c), (b,a,c) and all such permutations will be considered as the same triplet.

If the answer is greater than 109 + 7, print the answer modulo (%) 10^9 + 7.

Input Format
The first line contains an integer N, i.e., the number of vertices in tree.
The next N-1 lines represent edges: 2 space separated integers denoting an edge followed by a color of the edge.
 A color of an edge is denoted by a small letter of English alphabet, and it can be either red(r) or black(b).

Output Format
Print a single number i.e. the number of triplets.

Constraints
1 ≤ N ≤ 10^5
A node is numbered between 1 to N.

Sample Input

5
1 2 b
2 3 r
3 4 r
4 5 b
Sample Output

4
Explanation

Given tree is something like this.

 1 --- black --- 2 --- red --- 3 --- red --- 4 --- black --- 5

(2,3,4) is one such triplet because on all paths i.e 2 to 3, 3 to 4 and 2 to 4 there is at
 least one edge having red color.
(2,3,5), (1,3,4) and (1,3,5) are other such triplets.
Note that (1,2,3) is NOT a triplet, because the path from 1 to 2 does not have an edge with red color.

Another one that's tripping me up:
INPUT:
10
3 2 r
7 9 b
6 1 b
10 4 r
8 5 r
3 7 b
9 1 r
1 10 b
4 5 b

OUTPUT:
68
***/

/*
After some cogitation on this I realized that this is a compbinatorial problem on top of disjoint sets.
Here are the necessary facts:

 A. Since N <= 10^5, the number of triplets < 10^15 < 50 bits, so we can do all arithmetic with 'unsigned long long'
 B. The negation of the problem is easier to solve. I.e. how many triplets are such that the path between two of
 the vertices in the triplet is purely black.
 C. Define the black components B_1, B_2, ... , B_k to be the black edge connected VERTEX components and with
 respective cardinalities b_1, b_2, ... , b_k.
 D. For a path to be purely black, its endpoints must be in one of the B_i above.
 E. Therefore, the set of all triplets such that two vertices have a pure black path are the set of
 triplets such that two vertices are in one of the B_i.
 F. For every B_i the number of triples such that two are in B_i are given by:
    the number of ways to choose 2 verts in B_i and 1 outside of B_i + number of ways to choose 3 verts B_i
      =  C(b_i, 2) * (N-b_i) + C(b_i, 3)
 G. This gives us a final formula:
       Kundu's # = Total number of triplets - number of triples with 2 verts having pure black path
                 = C(N, 3) - Sum(i=1, k) { C(b_i, 2) * (N-b_i) + C(b_i, 3) }

 */

#include <iostream>
#include <vector>
#include <set>
//#include <climits>
using namespace std;

using ull = unsigned long long;
inline ull kunduTerm(ull N, ull b){
    ull bC2 = b*(b-1)/2;
//    cout << "bC2 = " << bC2 << endl;
//    cout << "bC2 * (N-b) = " << bC2 * (N-b) << endl;
//    cout << "bC2 * (b-2)/3 = " << bC2 * (b-2)/3 << endl;
    return bC2 * (N-b) + bC2 * (b-2)/3;
}

struct graph {
    graph (unsigned N) : N(N) , G(N) {
        unsigned from , to;
        char color;
        for (unsigned i = 1; i <= N - 1; ++i) {
            cin >> from >> to >> color;
            G[from - 1].push_back(make_pair(to - 1 , color));
            G[to - 1].push_back(make_pair(from - 1 , color));
        }
    }

    const unsigned N;

    //DFS:
    vector<set<unsigned>> getBlackComponents () {
        vector<set<unsigned>> result;
        bool *visited = new bool[N];
        for(int i=0; i<N; ++i) {visited[i] = false;}
        for (unsigned from = 0; from < N; ++from) {
            if (visited[from]) { continue; }
            set<unsigned> currComp;
            vector<unsigned> stack;
            stack.push_back(from);
            while (stack.size()) {
                unsigned visiting = stack.back();
                stack.pop_back();
                visited[visiting] = true;
                currComp.insert(visiting);
                for(auto toNcolor: G[visiting]){
                    unsigned to = toNcolor.first;
                    if(toNcolor.second == 'b' && !visited[to]){
                        stack.push_back(to);
                    }
                }
            }
            if(currComp.size() >= 2){
                result.push_back(currComp);
            }
        }
        delete[] visited;
        return result;
    }

    vector<size_t> getBlackComponentSizes(){
        vector<set<unsigned>> blackComps = getBlackComponents();
        vector<size_t> result(blackComps.size());
        transform(blackComps.cbegin(), blackComps.cend(), result.begin(), [](set<unsigned> x){return x.size();});
        return result;
    }

    ull getKunduAnswerWithoutModulus(){
        auto b = getBlackComponentSizes();
        ull result = N*(N-1)/2 * (N-2)/3;
        cout << "result_begin = " << result << endl;
        for(auto b_i: b){
            auto kt = kunduTerm(N, b_i);;
            cout << "kt[" << b_i << "] = " << kt << endl;
            result -= kt;
        }
        cout << "result_end = " << result << endl;
        return result;
    }

    void print () {
        for (unsigned from = 1; from <= N; ++from) {
            for (auto toNcolor: G[from - 1]) {
                cout << from << " --" << toNcolor.second << "-- " << (toNcolor.first + 1) << endl;
            }
        }

    }

private:
    //adjacency list. edge (i,j) represented by (i-1) --> <(j-1), color> and vice versa
    vector< vector< pair<unsigned , char> > > G;
};

int main(){
    cout << "ULLONG_MAX = " << ULLONG_MAX << endl;
    cout << "ULONG_MAX = " << ULONG_MAX << endl;
    cout << "UINT_MAX = " << UINT_MAX << endl;
    unsigned N;
    cin >> N;
    graph G(N);
    G.print();
    auto blackComps = G.getBlackComponents();
    for(auto comp: blackComps){
        cout << "\nComponent: ";
        for (auto x: comp){ cout << x << ", "; }
    }
    auto compSizes = G.getBlackComponentSizes();
    cout << "\nSizes: ";
    for(auto x: compSizes){ cout << x << ", "; }

    //cout << "\nANSWER IS: ";
    cout << G.getKunduAnswerWithoutModulus() % 1000000007ULL;
    return 0;
}