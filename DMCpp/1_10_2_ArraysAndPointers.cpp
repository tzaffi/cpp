//
// Created by zeph on 11/14/16.
//
#include <iostream>

template<typename num>
void fillFibArray(size_t N, num* fib){
    int pos = 0;
    if (pos >= N) return;
    fib[pos++] = 0;
    if (pos >= N) return;
    fib[pos++] = 1;
    for(; pos < N; fib[pos] = fib[pos-2] + fib[pos-1], ++pos);
}

template<typename num>
void printFiArray(size_t N, num* fib){
    for(int i=0; i<N; i++){
        std::cout << "f_" << i << " = " << fib[i] << std::endl;
    }
}

int main(){
    using namespace std;
    cout << "PART 1: Pointer Stuff" << endl << endl;
    const char* myName= "Zeph Grunschlag";

    cout << "myName = " << myName << endl;
    const char* pointerToAchar = &myName[5];
    cout << "pointerToAchar = " << pointerToAchar << endl;
    cout << "*pointerToAchar = " << *pointerToAchar << endl;

    int arrayOf10ints[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    cout << "arrayOf10ints = " << arrayOf10ints << endl;
    int(* ptrToArrayOf10Ints)[10] = &arrayOf10ints;
    cout << "ptrToArrayOf10Ints = " << ptrToArrayOf10Ints << endl;

    const char *ptrToArrayOfCharStrings[] = {"hi", "mom", "Trump", "sucks!"};
    cout << "ptrToArrayOfCharStrings = " << ptrToArrayOfCharStrings << endl;

    char a('a');
    char* aPtr = &a;
    char **ptrToPtrToChar = &(aPtr);
    cout << "ptrToPtrToChar = " << ptrToPtrToChar << endl;

    (**ptrToPtrToChar) = 'b';
    cout << "now a is ACTUALLY " << a << endl;

    const int intConst(17);
    cout << "intConst = " << intConst << endl;

    const int* ptrTointConst = &intConst;
    cout << "ptrTointConst = " << ptrTointConst << endl;
    //shouldn't compile (and id doesn't, hense must comment out):
    // *ptrTointConst = 19;

    //but this should:
    const int anotherIntConst(13);
    ptrTointConst = &anotherIntConst;
    cout << "After re-assignments: ptrTointConst = " << ptrTointConst << endl;

    int * const constPtrToInt(&arrayOf10ints[5]);
    cout << "constPtrToInt = " << constPtrToInt << endl;
    cout << "*constPtrToInt = " << *constPtrToInt << endl;
    //Shouldn't compile:
    //constPtrToInt = &arrayOf10ints[4];

    cout << "PART 1 UPSHOT. This stuff is confusing but the \"Clockwise/Spiral Rule\" is your friend"
         << "http://c-faq.com/decl/spiral.anderson.html" << endl;

    cout << endl << endl << "PART 2: On the stack and heap / valgrind" << endl << endl;
    const unsigned long fibSize = 100;

    cout << "A " << fibSize << " Fibonacci's on the stack";
    unsigned long fibStack[fibSize];
    fillFibArray(fibSize, fibStack);
    printFiArray(fibSize, fibStack);

    cout << "How big an array?" << endl << "> ";
    unsigned long fibSize2;
    cin >> fibSize2;
    unsigned long *fibHeap = new unsigned long[fibSize2];
    fillFibArray(fibSize2, fibHeap);
    printFiArray(fibSize2, fibHeap);
    delete[] fibHeap;


    cout << "How big an array to re-allocate?" << endl << "> ";
    cin >> fibSize2;
    fibHeap = new unsigned long[fibSize2];
    fillFibArray(fibSize2, fibHeap);
    printFiArray(fibSize2, fibHeap);
    cout << "OOOOOPS!!!! forgot to delete[] !!!" << endl;
    cout << "Please run the command" << endl << "valgrind --tool=memcheck ./arraysAndPointers "
         << "to UNDERSTAND BETTER WHY." << endl << endl;
    //delete[] fibHeap;
/*
 * Valgrind's report (the relevant portion assuming fibsize2 = 100)
 *
==62157== LEAK SUMMARY:
==62157==    definitely lost: 800 bytes in 1 blocks
==62157==    indirectly lost: 0 bytes in 0 blocks
==62157==      possibly lost: 2,064 bytes in 1 blocks
==62157==    still reachable: 8,192 bytes in 2 blocks
==62157==         suppressed: 20,102 bytes in 188 blocks
==62157== Rerun with --leak-check=full to see details of leaked memory
 *
 */

    return 0;
}