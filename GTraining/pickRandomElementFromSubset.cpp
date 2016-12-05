//
// Created by zeph on 12/4/16.
//

#include <iostream>
#include <vector>
#include <set>
#include <random>
#include <map>

using namespace std;

template <typename T>
class randomElementFromSubset
{
public:
    randomElementFromSubset(const vector<pair<T,double>>& valuesAndWeights){
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        generator = default_random_engine(seed);
        for(auto p: valuesAndWeights){
            values.push_back(p.first);
            weights.push_back(p.second);
        }
    }
    /**
     *
     * @param from subset to choose from
     * @return randomly chosen value according to its relative weight from the "from" subset, or "" if not present
     * in subset
     */
    T getRandomValue(const set<T>& from){
        double total = 0.0;
        vector<T> fromVals;
        vector<double> wTotals;
        for(size_t i = 0; i<values.size(); ++i){
            string val = values[i];
            double weight = weights[i];
            if(from.find(val) == from.end()){ continue; }
            fromVals.push_back(val);
            wTotals.push_back(total + weight);
            total += weight;
        }
        if(total == 0.0){ return string(""); }

        uniform_real_distribution<double> distribution(0.0, total);
        double rndNumber = distribution(generator);
        for(size_t i = 0; i<fromVals.size() - 1; ++i){
            if( rndNumber < wTotals[i]) {
                return fromVals[i];
            }
        }
        return *fromVals.crbegin();
    }

    void print() const{
        for(size_t i = 0; i<values.size(); ++i){
            cout << values[i] << "[" << weights[i] << "], " ;
        }
    }
private:
    default_random_engine generator;
    vector<T> values;
    vector<double> weights;
};


using wString = pair<string, double>;

int main(){
    cout << "Random Element from Subset\n\n";

    randomElementFromSubset<string> refs({make_pair("zeph", 0.2),
                                  make_pair("yoonie", 0.3),
                                  make_pair("sareva", 0.1),
                                  make_pair("shalev", 0.25),
                                  make_pair("leo", 0.25)
                                 });
    refs.print();

    set<string> subset({"sareva"});
    cout << "\n\nPick random from {\"sareva\"}\n\n";
    string rs = refs.getRandomValue(subset);
    cout << "[" << rs << "]" << endl;

    subset = {"leo", "sareva", "yoonie", "zeph", "daniel"};
    cout << "\n\nPick random from {\"leo\", \"sareva\", \"yoonie\", \"zeph\", \"daniel\"}\n";
    cout << "[" << refs.getRandomValue(subset) << "]" << endl;
    cout << "[" << refs.getRandomValue(subset) << "]" << endl;
    cout << "[" << refs.getRandomValue(subset) << "]" << endl;
    cout << "[" << refs.getRandomValue(subset) << "]" << endl;
    cout << "[" << refs.getRandomValue(subset) << "]" << endl;
    cout << "[" << refs.getRandomValue(subset) << "]" << endl;

    size_t N = 10000;
    map<string, unsigned> counter;
    for(int i=0; i<N; ++i){
        counter[refs.getRandomValue(subset)]++;
    }
    cout << "results after a " << N << " tries:\n\n";
    for(auto x: counter){
        cout << x.first << ": " << x.second << "\t(" << (x.second*1.0)/N << "%)" << endl;
    }
    return 0;
}