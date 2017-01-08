//
// Created by zeph on 1/7/17.
//

#include <iostream>
#include <set>
#include <map>
#include <vector>

class graph{
public:
    friend std::ostream& operator<<(std::ostream& os, const graph& g);
    graph(unsigned E) : E(E){
        using namespace std;
        string from, to;
        for(unsigned i=1; i<=E; ++i){
            cin >> from >> to;
            if(!G.count(from)){
                G[from] = set<string>();
                inDegs[from] = 0;
                roots.insert(from);
            }
            if(!G.count(to)){
                G[to] = set<string>();
                inDegs[to] = 0;
                roots.insert(to);
            }
            G[from].insert(to);
            inDegs[to]++;
            roots.erase(to);
        }
    }

    std::vector<std::string> topologicalSort() const{
        using namespace std;
        vector<string> result;
        graph gCopy(*this);
        while(gCopy.roots.size()){
            result.push_back(gCopy.topSortStep());
        }
        return result;
    }
private:
    unsigned E; //purported number of edges... with possible duplicates
    std::map<std::string, std::set<std::string>> G;
    std::map<std::string, unsigned> inDegs;
    std::set<std::string> roots; // have indegree 0

    std::string topSortStep(){
        using namespace std;
        if(!roots.size()){ throw "Ill defined graph as must have root for topological sorting!!!"; }
        string root = *roots.begin();
        roots.erase(root);
        for(const auto& to: G[root]){
            inDegs[to]--;
            if(inDegs[to] == 0){
                roots.insert(to);
            }
        }
        G.erase(root);
        return root;
    }
};

std::ostream& operator<<(std::ostream& os, const graph& g){
    using namespace std;
    for(const auto& outBound: g.G){
        string from = outBound.first;
        cout << endl << "[" << g.inDegs.at(from) << ":]" << from << "[: " << outBound.second.size() << "] --> ";
        for(const auto& to: outBound.second){
            cout << to << ", ";
        }
    }
    return os;
}


int main(){
    using namespace std;
    unsigned E;
    cin >> E;
    graph g(E);
    cout << g;
    vector<string> topSorted = g.topologicalSort();
    cout << endl << "Top sorting is: \n";
    for(auto x: topSorted){ cout << x << "-->"; }
    return 0;
}
