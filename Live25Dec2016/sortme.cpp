//
// Created by zeph on 12/25/16.
//

#include <iostream>
#include <random>
#include <fstream>
#include <set>
#include <cassert>
#include <queue>

// reset as necessary to the max working memory on your machine:
const size_t MAX_MEMORY = 1024 * 1024 * 1024;
// play it safe and only allow a fraction for in-memory sorting
const unsigned RATIO_OF_WORKING_TO_SORTING_MEMORY = 4;
const size_t MAX_SORTING_MEMORY = MAX_MEMORY / RATIO_OF_WORKING_TO_SORTING_MEMORY;


//little data structure to store in the merger heap:
using pqPair = std::pair<size_t, std::string>;
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
    //reverse order for the priority_queue to be a min-heap:
    bool operator() (const pqPair& lhs, const pqPair & rhs) const{
        return (*this)(rhs.second, lhs.second);
    }

private:
//    bool reverse;

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

template <typename C>
class largeTextFileSorter {
public:
    largeTextFileSorter(const std::string& inputFilename,
                        const std::string& outputFilename,
                        size_t maxSortingMemory = MAX_SORTING_MEMORY) :
            inputFilename(inputFilename),
            outputFilename(outputFilename),
            maxSortingMemory(maxSortingMemory)
    {}

    void runSortingAlgorithm(){
        std::cout << "running the sorting algorithm from "
                  << inputFilename << " >--to--> "
                  << outputFilename << std::endl;
        std::cout << "Memory requirements\n\tSorting Memory: "
                  << maxSortingMemory << "B\n";
        numChunks = makeSmallSortedChunks();
        runMultiMerge();
        cleanup();
    }

private:
    const std::string inputFilename;
    const std::string outputFilename;
    const size_t maxSortingMemory;
    unsigned numChunks;

    /**
     * Read the input and write into sorted chunks using MAX_SORTING_MEMORY to determine the size of each chunk.
     * Chunks are stored in temporary files prefixed by __ and in the same directory as the input.
     * This is not ideal. Should really save to a new subdirectory, but this is OS specific and requires
     * external libraries such as Boost.
     * @return the number of chunks created
     */
    uint makeSmallSortedChunks () {
        std::cout << "making small sorted chunks\n";
        std::ifstream infile;
        // was generating exception for "unspecified" reason. In production code would bring back in and investigate further:
        //infile.exceptions(std::ios_base::badbit | std::ios_base::failbit);

        infile.open(inputFilename);
        if ( infile.peek() == std::ifstream::traits_type::eof() )
        {
            // Empty File - so return 0
            infile.close();
            return 0;
        }

        size_t chunkNum = 0, chunkSize = 0;
        std::multiset<std::string, C> chunkSet;

        std::string line;
        while (std::getline(infile, line))
        {
            //std::cout << line << std::endl;
            size_t lineMemory = line.size() + 1; // add 1 for newline char
            if(chunkSize + lineMemory <= maxSortingMemory){
                chunkSize += lineMemory;
                chunkSet.insert(line);
            } else {
                writeChunkAndClearSet(chunkSet, chunkNum);
                ++chunkNum;
                chunkSize = lineMemory;
                chunkSet.insert(line);
            }
        }
        //Always one more chunk:
        writeChunkAndClearSet(chunkSet, chunkNum);
        //0 indexed so add 1:
        infile.close();
        return chunkNum+1;
    }

    /*
     * Read all chunk files simultaneously keeping the last read line from each file in a priority_queue.
     */
    void runMultiMerge() {
        //get file streams and populate heap with first line of each:
        std::priority_queue<pqPair , std::vector<pqPair>, C> mergerHeap;
        //std::vector<std::shared_ptr<std::ifstream>> chunkStreams;
        std::ifstream* chunkStreams[numChunks];
        std::string line;
        for(size_t chunkNum = 0; chunkNum < numChunks; ++chunkNum){
            std::string chunkFilename = getChunkFilename(chunkNum);
            std::cout << "Opening chunk file " << chunkFilename << " for merge\n";
            std::ifstream* infile = new std::ifstream();
            infile->open(chunkFilename);
            chunkStreams[chunkNum] = infile;
            //by design, no empty files so can initialize heap:
            std::getline(*infile, line);
            mergerHeap.push(std::make_pair(chunkNum,line));
        }

        std::ofstream outputFstream;
        outputFstream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        outputFstream.open(outputFilename);

        //read current min from heap, replacing it by the next line from same file if possible
        //if not possible, just skip
        while(!mergerHeap.empty()){
            pqPair next = mergerHeap.top();
            outputFstream << next.second << std::endl;
            mergerHeap.pop();
            size_t chunkNum = next.first;
            if(std::getline(*chunkStreams[chunkNum], line)){
                mergerHeap.push(std::make_pair(chunkNum, line));
            }
        }
        outputFstream.close();

        std::cout << "Closing all the chunk files.\n";
        for(size_t chunkNum = 0; chunkNum < numChunks; ++chunkNum){
            chunkStreams[chunkNum]->close();
            delete chunkStreams[chunkNum];
        }
    }

    static inline std::string getChunkFilename (size_t chunkNum) {
        return std::string("__") + std::to_string(chunkNum);
    }

    /**
     * Write an entire chunk to a file, and clear the input set for use with next chunk
     * @param chunkSet
     * @param chunkNum
     */
    void writeChunkAndClearSet (std::multiset<std::string, C> &chunkSet, size_t chunkNum) {
        std::string chunkFilename = getChunkFilename(chunkNum);
        std::cout << "Writing chunk #" << chunkNum << " to " << chunkFilename << std::endl;
        std::ofstream chunkFstream;
        chunkFstream.exceptions(std::ios_base::badbit | std::ios_base::failbit);
        chunkFstream.open(chunkFilename);

        for(std::string line : chunkSet){
            chunkFstream << line << std::endl;
        }
        chunkFstream.close();
        chunkSet.clear();
    }

    /**
     * Delete all the temporary chunkfile detritous
     */
    void cleanup () {
        for(size_t chunkNum = 0; chunkNum < numChunks; ++chunkNum){
            std::string fileToDelete = getChunkFilename(chunkNum);
            remove(fileToDelete.c_str());
            std::cout << "Deleting chunk file " << fileToDelete << std::endl;
        }
    }

};

int main(int argc, char** argv) {
    using namespace std;
    assert(argc >= 3);
    size_t sortingMemory = MAX_SORTING_MEMORY;

    cout << "argv[0]: " << argv[0] << endl;
    cout << "argv[1]: " << argv[1] << endl;
    cout << "argv[2]: " << argv[2] << endl;
    if (argc > 3){
        cout << "argv[3]: " << argv[3] << endl;
        sortingMemory = stoll(argv[3]) / RATIO_OF_WORKING_TO_SORTING_MEMORY;
    }



    string executableName(argv[0]);
    cout << "Max sorting memory for " << executableName << " is " << sortingMemory << "B\n";

    string inputFilename(argv[1]);
    string outputFilename(argv[2]);

    cout << "inputFilename = " << outputFilename << endl;
    cout << "outputFilename = " << outputFilename << endl;

    largeTextFileSorter<sCountComparator> fileSorter(inputFilename, outputFilename, sortingMemory);
    fileSorter.runSortingAlgorithm();
    return 0;
}