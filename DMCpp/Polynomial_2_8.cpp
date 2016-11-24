//
// Created by zeph on 11/24/16.
//

#include "Polynomial_2_8.h"

#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

polynomial::polynomial(const unsigned& degree) : D(degree), m_coeffs(D+1, 0.0) {}

//TODO: complaints about possible negative
polynomial::polynomial (const std::vector<double> &coeffs) :
        D(coeffs.size()-1), m_coeffs(coeffs) { }

polynomial &polynomial::operator= (polynomial &&rhs) {
    D = move(rhs.D);
    m_coeffs = move(rhs.m_coeffs);
    rhs.D = 0;
    rhs.m_coeffs =  vector<double>();
    return *this;
}

polynomial f(double c2, double c1, double c0){
    polynomial P({c0, c1, c2});
    return P;
}

const unsigned& polynomial::degree() const { return D;}
void polynomial::assignCoefficients (const std::vector<double>& coeffs) {
    assert(coeffs.size() <= D+1); //TODO: use exceptions instead
    size_t i=0;
    for(; i<coeffs.size(); ++i) {
        m_coeffs[i] = coeffs[i];
    }
    for(; i<=D; ++i) {
        m_coeffs[i] = 0.0;
    }
}
double polynomial::getCoefficient (unsigned i) const {
    assert(i <= D);
    return m_coeffs[i];
}

ostream &operator<< (ostream &os, const polynomial &P) {
    if(P.D==0){
        os << "NULL";
        return os;
    }
    for(size_t i=0; i<=P.D; ++i) {
        string prefix(""), suffix("");
        if(i > 0){
            prefix = " + ";
            suffix = string(" X") + (i > 1 ? string("^") + to_string(i) : string(""));
        }
        os << prefix << P.m_coeffs[i] << suffix;
    }
    return os;
}

polynomial::~polynomial () {
    cout << "Good bye. It was nice being " << endl << *this << endl;
    cout << "Do nothing as no memory is being managed directly\n";
}


int main(){
    cout << "Polynomial OO Exercises\n";
    polynomial quadratic(2);
    assert(quadratic.degree() == 2);
    cout << "Should print out 0 + 0 x + 0 x^2:\n";
    cout << quadratic << endl;

    quadratic.assignCoefficients({1,2,3}); // 1 + 2x + 3x^2
    assert(quadratic.getCoefficient(2) == 3.0);

    polynomial quartic({5,4,3,2,1});
    assert(quartic.degree() == 4);
    cout << "quartic = " << endl << quartic << endl << endl;

    cout << "what happens with a single double?";
    polynomial unclear(2.3);
    cout << "unclear = " << endl << unclear << endl;

    cout << "what happens with a single {double}?";
    polynomial unclear2{2.3};
    cout << "unclear2 = " << endl << unclear2 << endl;

    cout << "what happens with a single ({double})?";
    cout << "\n\n DOES NOT COMPILE!!!\n\n";

    cout << "what happens with vector<double>{4.0}";
    polynomial unclear3(vector<double>{4.0});
    cout << "unclear3 = " << endl << unclear3 << endl;

    unclear2 = f(100, 50, 25);
    cout << unclear2 << endl;
    return 0;
}

