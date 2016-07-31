//
// Created by zeph on 7/30/16.
//
#include <iostream>

int main()
{
    //cf http://www.learncpp.com/cpp-tutorial/23-variable-sizes-and-the-sizeof-operator/
    using namespace std;
    cout << "Per Table 1-1\n";

    char c;
    short s;
    int i;
    long l;
    long long ll;
    unsigned u;
    signed S;
    float f;
    double d;
    long double ld;
    bool b;

    cout << "bool:\t\t" << sizeof(b) << " bytes" << endl;
    cout << "char:\t\t" << sizeof(c) << " bytes" << endl;
//    cout << "wchar_t:\t" << sizeof(wchar_t) << " bytes" << endl;
//    cout << "char16_t:\t" << sizeof(char16_t) << " bytes" << endl; // C++11, may not be supported by your compiler
//    cout << "char32_t:\t" << sizeof(char32_t) << " bytes" << endl; // C++11, may not be supported by your compiler
    cout << "short:\t\t" << sizeof(s) << " bytes" << endl;
    cout << "int:\t\t" << sizeof(i) << " bytes" << endl;
    cout << "signed:\t\t" << sizeof(S) << " bytes" << endl;
    cout << "long:\t\t" << sizeof(l) << " bytes" << endl;
    cout << "long long:\t" << sizeof(ll) << " bytes" << endl; // C++11, may not be supported by your compiler
    cout << "float:\t\t" << sizeof(f) << " bytes" << endl;
    cout << "double:\t\t" << sizeof(d) << " bytes" << endl;
    cout << "long double:\t" << sizeof(ld) << " bytes" << endl;
    cout << "&(long double):\t" << sizeof(&ld) << " bytes" << endl;
    cout << "&(char):\t" << sizeof(&c) << " bytes" << endl;
    return 0;
}