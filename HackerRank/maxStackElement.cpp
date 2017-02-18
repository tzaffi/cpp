//
// Created by zeph on 2/11/17.
//

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

struct maxStack{
    void push(unsigned x){
        s.push_back(x);
        if (x > _currMax){
            _currMax = x;
        }
    }
    unsigned currMax(){
        return _currMax;
    }
    void pop(){
        unsigned removed = s.back();
        s.pop_back();
        if(s.empty()){
            _currMax = 0;
        }
        else if(removed == _currMax){
            _currMax = 0;
            for(unsigned x: s){
                if(x > _currMax){
                    _currMax = x;
                }
            }
        }
    }
private:
    vector<unsigned> s;
    unsigned _currMax = 0;
};

int main() {
    maxStack ms;
    unsigned N;
    cin >> N;
    //cout << N;
    for(unsigned i = 1; i <= N; i = i+1){
        char type;
        cin >> type;
        //cout << "type = " << type << endl;
        if(type == '1'){
            unsigned x;
            cin >> x;
            //cout << "x = " << x << endl;
            ms.push(x);
        }else if(type == '2'){
            ms.pop();
        }else{
            cout << ms.currMax() << '\n';
        }
    }
    return 0;
}
