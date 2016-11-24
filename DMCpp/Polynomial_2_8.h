//
// Created by zeph on 11/24/16.
//

#ifndef CPP_POLYNOMIAL_2_8_H
#define CPP_POLYNOMIAL_2_8_H

#include <vector>
#include <ostream>

class polynomial {
public:
    polynomial(const unsigned& degree);
    polynomial(const std::vector<double>& coeffs);
    ~polynomial ();
    const unsigned& degree() const;
    void assignCoefficients(const std::vector<double>& coeffs);
    double getCoefficient(unsigned i) const;

    friend std::ostream &operator<< (std::ostream &os , const polynomial &P);

private:
    unsigned D;
    std::vector<double> m_coeffs;
};


#endif //CPP_POLYNOMIAL_2_8_H
