//
// Created by zeph on 12/28/16.
//
/*
Random number generator

        There is an ideal random number generator, which given a positive integer M
        can generate any real number between 0 to M, and probability density function is uniform in [0, M].

Given two numbers A and B and we generate x and y using the random number generator with uniform
 probability density function [0, A] and [0, B] respectively,
 what's the probability that x + y is less than C? where C is a positive integer.

Input Format

The first line of the input is an integer N, the number of test cases.

N lines follow. Each line contains 3 positive integers A, B and C.

Constraints

        All the integers are no larger than 10000.

Output Format

For each output, output a fraction that indicates the probability.
 The greatest common divisor of each pair of numerator and denominator should be 1.

Sample Input

3
1 1 1
1 1 2
1 1 3
Sample Output

1/2
1/1
1/1

============= Z comments ===========
After much deliberation I realized that this is an interesting math problem.
What is the random distribution resulting from adding to uniform distribution. The answer was non-trivial...

I was able to derive the following formulae:

Assuming a <= b.
X_c = random variable for the uniform distribution from 0 to a with probability density:
pdf_c(x) = 1/c if x in [0,c] else 0
and cumulative distribution:
cdf_c(x) = x/c if x in [0,c] else 0 if x < 0 else 1 if x > c

Then the resulting density and distribution of adding X_a + X_b is:
pdf_sum(x) = 0              if x < 0
             x/ab           if 0 <= x < a
             1/b            if a <= x < b
             1/b - (x-b)/ab if b <= x < a+b
             0              if a+b <=  x

cdf_sum(x) = 0                      if x < 0
             x^2 / 2ab              if 0 <= x < a
             (2x-a)/2b              if a <= x < b
             [2ab-(a+b-x)^2]/2ab    if b <= x < a+b
             1                      if a+b <= x

So that is what I'll be using below:
*/


#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cassert>

using namespace std;

/**
 * Compute the GCD using the Euclidean algorithm
 * @param a
 * @param b
 * @return the GCD
 */
int euclid(int a, int b){
    int r = a % b;
    while(r > 0){
        a = b, b = r;
        r = a % b;
    }
    return b;
}

/**
 * Compute the cumulitive density function of the sum of 2 uniform random variables:
 * cdf_sum(x) = 0                      if x < 0
             x^2 / 2ab              if 0 <= x < a
             (2x-a)/2b              if a <= x < b
             [2ab-(a+b-x)^2]/2ab    if b <= x < a+b
             1                      if a+b <= x
 * @param a - the first random is uniformly distributed on [0, a] and a <= b
 * @param b - the second random is uniformly distributed on [0, b] (and a <= b)
 * @param x - the point at which to evaluate the cdf
 * @return - the value of the cdf at x
 */
pair<unsigned, unsigned> cdfOfUniformRandVariables(int a, int b, int x){
    assert(a>0);
    assert(a<=b);
    pair<unsigned, unsigned> result;
    if(x <= 0){
        return make_pair(0,1);
    }else if (x >= a+b){
        return make_pair(1,1);
    }else if (x <= a){
        result.first = x*x;
        result.second = 2*a*b;
    }else if (x <=b){
        result.first = 2*x-a;
        result.second = 2*b;
    }else {
        int tmp = a+b-x;
        result.first = 2*a*b - tmp*tmp;
        result.second = 2*a*b;
    }

    int gcd = euclid(result.first, result.second);
    if(gcd != 1) {
        result.first /= gcd;
        result.second /= gcd;
    }
    return result;
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    unsigned numTestCases;
    cin >> numTestCases;
    unsigned a, b, c;
    for(int i = 1; i <= numTestCases; ++i){
        cin >> a >> b >> c;
        if(a>b){ swap(a,b); }
        auto rational = cdfOfUniformRandVariables(a, b, c);
        int p = rational.first, q = rational.second;
//        int p = c, q = (a+b);
//        if (p >= q){ p = 1; q = 1;}
//        else{ //run Euclid:
//            int gcd = euclid(p, q);
//            p /= gcd;
//            q /= gcd;
//        }
        cout << p << "/" << q << endl;
    }
    return 0;
}
