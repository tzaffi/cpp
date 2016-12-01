//
// Created by zeph on 11/29/16.
//
/*
433. Minimum Genetic Mutation

 A gene string can be represented by an 8-character long string, with choices from "A", "C", "G", "T".

Suppose we need to investigate about a mutation (mutation from "start" to "end"),
 where ONE mutation is defined as ONE single character changed in the gene string.

For example, "AACCGGTT" -> "AACCGGTA" is 1 mutation.

Also, there is a given gene "bank", which records all the valid gene mutations.
 A gene must be in the bank to make it a valid gene string.

Now, given 3 things - start, end, bank, your task is to determine what is the
 minimum number of mutations needed to mutate from "start" to "end". If there is no such a mutation, return -1.

Note:

1. Starting point is assumed to be valid, so it might not be included in the bank.
2. If multiple mutations are needed, all mutations during in the sequence must be valid.
3. You may assume start and end string is not the same.

 Example 1:

start: "AACCGGTT"
end:   "AACCGGTA"
bank: ["AACCGGTA"]

return: 1

Example 2:

start: "AACCGGTT"
end:   "AAACGGTA"
bank: ["AACCGGTA", "AACCGCTA", "AAACGGTA"]

return: 2
Example 3:

start: "AAAAACCC"
end:   "AACCCCCC"
bank: ["AAAACCCC", "AAACCCCC", "AACCCCCC"]

return: 3

Recall the pseudocode for DFS:

DFS(v, action):
  action(v)
  visited[v] = true;
  for each v' connected to v:
    if NOT visited[v']:
        DFS(v, action)

Or iteratively (with a stack):

DFS(v, action):
  stack.push(v)
  while stack.notEmpty():
      v = stack.pop()
      action(v)
      visited[v] = true;
      for each v' connected to v:
        if NOT visited[v']:
            stack.push(v')


Actually, we need BFS:
BFS(v, action):
  queue.put(v)
  while queue.notEmpty():
      v = queue.get()
      action(v)
      visited[v] = true;
      for each v' connected to v:
        if NOT visited[v']:
            queue.put(v')
*/

#include <iostream>
#include <vector>
#include <cassert>
#include <unordered_map>
#include <queue>

using namespace std;

class Solution {
public:
    int minMutation(string start, string end, vector<string>& bank) {
        buildGraph(start, bank);
        computeDistances(start, bank);
        return distancesFromStart.count(end) ? distancesFromStart[end] : -1;
    }
private:
    void buildGraph(const string& start, const vector<string>& bank){
        graph = unordered_map<string, vector<string>>();
        graph[start] = vector<string>();
        addEdges(start, bank);
        for(string v: bank){
            graph[v] = vector<string>();
            addEdges(v, bank);
        }
    }
    void addEdges (const string &x, const vector<string> &v) {
        for(string y: v){
            assert(x.size() == y.size());
            unsigned numdiffs = 0;
            for(unsigned i=0; i<x.size() && numdiffs < 2; ++i){
                if(x[i] != y[i]){
                    numdiffs++;
                }
            }
            if(numdiffs == 1){ graph[x].push_back(y); }
        }
    }
    void computeDistances(const string& start, const vector<string>& bank) {
        distancesFromStart = unordered_map<string, int>();
        for(string x: bank){ distancesFromStart[x] = -1; }
        distancesFromStart[start] = 0;
        queue<string> q;
        q.push(start);
        while(!q.empty()){
            string v = q.front(); q.pop();
            for(string w: graph[v]){
                if(distancesFromStart[w] == -1){
                    distancesFromStart[w] = distancesFromStart[v] + 1;
                    q.push(w);
                }
            }
        }
    }
    unordered_map<string, vector<string>> graph;
    unordered_map<string, int> distancesFromStart;
};

int main(){
    cout << "Mininmum Genetic Mutations aka Depth First Search\n\n";

    Solution s;

    string x = "AACCGGTT", y = "AACCGGTA";
    vector<string> bank = {"AACCGGTA"};
    assert(s.minMutation(x,y,bank) == 1);

    x = "AACCGGTT";
    y = "AAACGGTA";
    bank = {"AACCGGTA", "AACCGCTA", "AAACGGTA"};
    assert(s.minMutation(x,y,bank) == 2);

    x = "AAAAACCC";
    y = "AACCCCCC";
    bank ={"AAAACCCC", "AAACCCCC", "AACCCCCC"};
    assert(s.minMutation(x,y,bank) == 3);

    x = "AACCGGTT";
    y = "AACCGGTA";
    bank = {};
    assert(s.minMutation(x,y,bank) == -1);
    return 0;
}