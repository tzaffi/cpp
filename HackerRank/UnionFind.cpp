//
// Created by zeph on 1/6/17.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct Borg{
    Borg(unsigned id) : id(id), population(1) {}

    Borg* collapseToLeader(){
        if(parent){
            Borg *leader = parent->collapseToLeader();
            parent = leader;
            return leader;
        } else {
            return this;
        }
    }

    unsigned getCommunitySize(){
        Borg* leader = collapseToLeader();
        return leader->population;
    }


    //returns the "leader"
    Borg& merge(Borg& other){
        Borg *leader = collapseToLeader(), *otherLeader = other.collapseToLeader();
        if(leader->population >= otherLeader->population){
            otherLeader->parent = leader;
            leader->population += otherLeader->population;
            return *leader;
        }
        leader->parent = otherLeader;
        otherLeader->population += leader->population;
        return *otherLeader;
    }

    unsigned id;
    unsigned population;
    Borg *parent;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned N, Q;
    cin >> N >> Q;
    vector<Borg*> people;
    for(unsigned i=0; i<N; ++i){
        people.push_back(new Borg(i+1));
    }
//    for(auto p : people){
//        cout << "p = (id=" << p->id << ", pop=" << p->population << ")\n";
//    }
    string op;
    unsigned id1, id2;
    for(unsigned q=1; q<=Q; ++q){
        cin >> op;
//        cout << "op = " << op << endl;
        if(op == "Q"){
            cin >> id1;
            cout << people[id1-1]->getCommunitySize() << endl;
        }else{
            cin >> id1 >> id2;
            people[id1-1]->merge(*people[id2-1]);
        }
    }
    for(auto bptr: people){
        delete bptr;
    }
    return 0;
}
