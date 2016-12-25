//
// Created by zeph on 12/25/16.
//

#include <iostream>
#include <random>
#include <fstream>

using namespace std;

int main(int argc, char** argv) {
    srand((unsigned int)std::time(0));

    cout << "argv[0]: " << argv[0] << endl;
    cout << "argv[1]: " << argv[1] << endl;
    cout << "argv[2]: " << argv[2] << endl;
    cout << "argv[3]: " << argv[3] << endl;

    long long fileLen = stoll(argv[1]);
    int maxNumS = stoi(argv[2]);
    string outputFilename(argv[3]);

    cout << "fileLen = " << fileLen << endl;
    cout << "maxNumS = " << maxNumS << endl;
    cout << "outputFilename = " << outputFilename << endl;

    ofstream outfile;
    outfile.exceptions(ios_base::badbit | ios_base::failbit);
    outfile.open(outputFilename);

    for(long long i=0; i<fileLen; ++i){
        size_t lineLen = rand() % (maxNumS + 1);
        for(int i = 0; i < lineLen; ++i){
            char ess = (rand() % 2 ? 's' : 'S');
            outfile << ess;
        }
        outfile << endl;
    }
    outfile.close();

    return 0;
}