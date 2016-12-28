#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
using namespace std;

unordered_map<string, string> buildHRMLdict(unsigned N){
    unordered_map<string, string> result;
    vector<string> scope;
    string line;
    for(int i=0; i<N; ++i){
        getline(cin, line);
        //cout << "got: " << line << endl;
        if(line[1] == '/'){
            scope.pop_back();
            continue;
        }
        stringstream tagSS(line);
        char c;
        string tag;
        tagSS >> c >> tag;
        bool end = tag[tag.size()-1] == '>';
        if(end){ tag = tag.substr(0, tag.size()-1); }
        scope.push_back(tag);
        while(!end){
            string attribute;
            tagSS >> attribute;
            //cout << attribute << endl;
            string eq, val;
            tagSS >> eq >> val;
            end = val[val.size()-1] == '>';
            if(end){ val = val.substr(0, val.size()-1); }
            string key = scope[0];
            for(unsigned i=1; i<scope.size(); ++i){
                key += string(".") + scope[i];
            }
            key += string("~") + attribute;
            result[key] = val.substr(1,val.size()-2);
            //cout << "Saved: " << key << "--->" << val << endl;
        }

    }
    return result;
}

void runQueries(const unordered_map<string, string>& dict, unsigned Q){
    string line;
    for(int i=0; i<Q; ++i){
        getline(cin, line);
        if(dict.count(line)){
            cout << dict.at(line) << endl;
        } else {
            cout << "Not Found!\n";
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    string line;
    getline(cin, line);
    //cout << line << endl;
    stringstream ls(line);
    unsigned N, Q;
    ls >> N >> Q;
    auto dict = buildHRMLdict(N);
    runQueries(dict, Q);
    return 0;
}
