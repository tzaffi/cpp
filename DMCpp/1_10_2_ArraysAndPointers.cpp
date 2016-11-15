//
// Created by zeph on 11/14/16.
//
#include <iostream>

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


    return 0;
}