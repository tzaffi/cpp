//
// Created by zeph on 1/8/17.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct graph{
    graph(unsigned N) : N(N), M(N) {
        for(unsigned i=0; i<N; ++i){
            cin >> M[i];
        }
    }
    const unsigned N;

    //DFS:
    unsigned getNumClusters(){
        unsigned numClusters = 0;
        bool* visited = new bool[N];
        for(unsigned vert=0; vert<N; ++vert){
            if(visited[vert]){ continue; }
            numClusters++;
            vector<unsigned> stack;
            stack.push_back(vert);
            while(stack.size()){
                unsigned visiting = stack.back();
                stack.pop_back();
                visited[visiting] = true;
                for(unsigned next = 0; next<N; ++next){
                    if(!visited[next] && M[visiting][next] == '1'){
                        stack.push_back(next);
                    }
                }
            }
        }
        delete[] visited;
        return numClusters;
    }

    void print(){
        for (auto x: M){ cout << x << endl; }
    }
private:
    vector<string> M; //adjacency matrix
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    ull N;
    cin >> N;
    graph G(N);
    //G.print();
    cout << G.getNumClusters();
    return 0;
}
