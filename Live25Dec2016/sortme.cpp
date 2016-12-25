//
// Created by zeph on 12/25/16.
//

#include <iostream>
#include <random>
#include <fstream>
//#include <sstream>

// reset as necessary to the max working memory on your machine:
const size_t MAX_MEMORY = 1024 * 1024 * 1024;
// play it safe and only allow a fraction for in-memory sorting
const size_t MAX_SORTING_MEMORY = MAX_MEMORY / 4;

template <typename C>
class largeTextFileSorter {
public:
    largeTextFileSorter(const std::string& inputFilename, const std::string& outputFilename) :
            inputFilename(inputFilename), outputFilename(outputFilename)
    {}

    void runSortingAlgorithm(){
        std::cout << "running the sorting algorithm from "
                  << inputFilename << " >--to--> "
                  << outputFilename << std::endl;
        numChunks = makeSmallSortedChunks();
    }

private:
    const std::string inputFilename;
    const std::string outputFilename;
    std::vector<std::string> tempFilenames;
    unsigned numChunks;

    /**
     * Read the input and write into sorted chunks using MAX_SORTING_MEMORY to determine the size of each chunk.
     * @return the number of chunks created
     */
    uint makeSmallSortedChunks () {
        std::cout << "making small sorted chunks\n";
        std::ifstream infile;
        infile.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        infile.open(inputFilename);
        std::string line;
        while (std::getline(infile, line))
        {
            std::cout << line << std::endl;
        }

//    ofstream outfile;
//    outfile.exceptions(ios_base::badbit | ios_base::failbit);
//    outfile.open(outputFilename);
//
//    for(long long i=0; i<fileLen; ++i){
//        size_t lineLen = rand() % (maxNumS + 1);
//        for(int i = 0; i < lineLen; ++i){
//            char ess = (rand() % 2 ? 's' : 'S');
//            outfile << ess;
//        }
//        outfile << endl;
//    }
//    outfile.close();
        return 0;
    }

};

/**
 * Compare by the number of s's in the string. Ignore case.
 *
 * We could optimize by stopping the count when we have a clear winner.
 */
struct sCountComparator {
    bool operator() (const std::string& lhs, const std::string& rhs) const
    {
        return numEsses(lhs) < numEsses(rhs);
    }

private:
    /**
     * Count the number of s's in the input ignoring case
     * @param str - string to consider
     * @return
     */
    size_t numEsses (const std::string &str) const {
        size_t cnt = 0;
        for(char c: str){
            if(c == 's' || c == 'S'){ cnt++; }
        }
        return cnt;
    }
};

int main(int argc, char** argv) {
    using namespace std;

    cout << "argv[0]: " << argv[0] << endl;
    cout << "argv[1]: " << argv[1] << endl;
    cout << "argv[2]: " << argv[2] << endl;

    string executableName(argv[0]);
    cout << "Max working memory for " << executableName << " is " << MAX_MEMORY << "B\n";
    cout << "Max sorting memory per file is " << MAX_SORTING_MEMORY << "B\n";

    string inputFilename(argv[1]);
    string outputFilename(argv[2]);

    cout << "inputFilename = " << outputFilename << endl;
    cout << "outputFilename = " << outputFilename << endl;

    largeTextFileSorter<sCountComparator> fileSorter(inputFilename, outputFilename);
    fileSorter.runSortingAlgorithm();
    return 0;
}