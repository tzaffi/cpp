//
// Created by zeph on 1/14/17.
//

#include <iostream>

template<typename T, unsigned N>
size_t array_size(const T (&array)[N])
{
    return N;
};

struct customType{
    int x, y, z, w;
    std::string s;
};

int main(){
    using namespace std;
    cout << "showing how to create a array_size(array) function\n";

    int x[10];
    cout << "array_size of 'int x[10]': " << array_size(x) << endl;
    cout << "sizeof(x) / sizeof(x[0]) = " <<  sizeof(x) << " / " << sizeof(x[0]) << " = " << sizeof(x)/sizeof(x[0]) << endl;

    float v[] = {1.0, 2.0, 3.0, 4.0};
    cout << "array_size of 'float v[] = {1.0, 2.0, 3.0. 4.0}': " << array_size(v) << endl;

    double m[4][5][6];
    cout << "array_size of 'double m[4][5][6]': " << array_size(m) << endl;
    cout << "array_size of 'm[0]': " << array_size(m[0]) << endl;
    cout << "array_size of 'm[0][0]': " << array_size(m[0][0]) << endl;
    //doesn't compile: cout << "array_size of 'm[0][0][0]': " << array_size(m[0][0][0]) << endl;

    customType c[30];
    cout << "array_size of 'customType c[30]': " << array_size(c) << endl;
    cout << "sizeof(c) / sizeof(c[0]) = "  <<  sizeof(c) << " / " << sizeof(c[0]) << " = " << sizeof(c)/sizeof(c[0]) << endl;

    unsigned long long ull;
    cout << "sizeof(unsigned long long ull) = " << sizeof(ull) << endl;

    cout << endl << "Now we expect some problems: " << endl;
    cout << "please enter array size N: ";
    unsigned N;
    cin >> N;
    cout << "Thank you!" << endl;
    int dyn[N];
    //cout << "size of 'int dyn[N]': " << size(dyn) << endl;
    cout << "sizeof(dyn) / sizeof(dyn[0]) = "  <<  sizeof(dyn) << " / " << sizeof(dyn[0]) << " = " << sizeof(dyn)/sizeof(dyn[0]) << endl;
    return 0;
}