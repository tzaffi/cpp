//
// Created by zeph on 11/25/16.
//
/*
 * In the interview prep at coogle, Sam Greenfiled pointed out that
 *   o map's basic operations run in O(log n) since it's backed by a BST
 *   while
 *   o unordered_map's is a true hash table with O(1) operations
 *
 *  Let's test this theory out.
 */

#include <iostream>
#include <map>
#include <unordered_map>
#include <cassert>

#include "../helpers/coutFriends.cpp"

using namespace std;
using namespace std::chrono;
using hires = std::chrono::high_resolution_clock;

vector<int> makeRandomVector (size_t N) {
    vector<int> randVect(N);
    generate(randVect.begin(), randVect.end(), [](){return rand();});
    return randVect;
}

template <typename M>
long long int populateMap (const vector<int> &v, M &table) {
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for(auto x: v){
        table[x] = x;
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    auto duration = duration_cast<chrono::microseconds>(t2 - t1 ).count();
    return duration;
}

template <typename M>
long long int retrieveAllFromMap (const vector<int> &v, const M &table) {
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for(auto x: v){
        assert(table.count(x) == 1);
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    auto duration = duration_cast<chrono::microseconds>(t2 - t1 ).count();
    return duration;
}

template <typename M>
long long int retrieveNonExistingFromMap (const vector<int> &v, const M &table) {
    chrono::steady_clock::time_point t1 = chrono::steady_clock::now();
    for(auto x: v){
        assert(table.count(837497) == 0);
    }
    chrono::steady_clock::time_point t2 = chrono::steady_clock::now();
    auto duration = duration_cast<chrono::microseconds>(t2 - t1 ).count();
    return duration;
}


void runExperiment (size_t N) {
    cout << "\n************************\n" << "Experiment with size N = " << N << endl;
    cout << "************************\n" << endl;
    vector<int> randVect{makeRandomVector(N)};
    //cout << "randVect = \n" << randVect << endl << endl;

    map<int, int> tableBST;
    long long int duration1a = populateMap(randVect, tableBST);
    cout << duration1a << " microseconds to populate Map with " << randVect.size() << " elements\n";

    unordered_map<int, int> tableHash;
    long long int duration1b = populateMap(randVect, tableHash);
    cout << duration1b << " microseconds for Unordered_Map with " << randVect.size() << " elements\n";

    long long int duration2a  = retrieveAllFromMap(randVect, tableBST);
    cout << duration2a << " microseconds to find all " << randVect.size() << " existing elements in Map\n";

    long long int duration2b  = retrieveAllFromMap(randVect, tableHash);
    cout << duration2b << " microseconds to find all " << randVect.size() << " existing elements in Unordered_Map\n";


    long long int duration3a  = retrieveNonExistingFromMap(randVect, tableBST);
    cout << duration3a << " microseconds to find all " << randVect.size() << " NON-existing elements in Map\n";

    long long int duration3b  = retrieveNonExistingFromMap(randVect, tableHash);
    cout << duration3b << " microseconds to find all " << randVect.size() << " NON-existing elements in Unordered_Map\n";

    cout << "----------SUMMARY----------\n";
    string u("UNDEFINED");
    cout << "Map is " << (duration1b ? to_string(duration1a / double(duration1b)) : u) << "X slower than unordered_map for population\n";
    cout << "Map is " << (duration3b ? to_string(duration2a / double(duration2b)) : u) << "X slower than unordered_map for retrieval existing\n";
    cout << "Map is " << (duration3b ? to_string(duration3a / double(duration3b)) : u) << "X slower than unordered_map for retrieval NON-existing\n";
}

int main (int argc, char* argv[])
{
    std::srand((unsigned int)std::time(0));

    for(size_t N = 1; N <= 10000000; N*=10) {
        runExperiment(N);
    }

    return 0;
}

